#pragma once

namespace distortion {
class distortion {
public:
  enum class DistType : size_t {
    soft = 0,
    hard = 1
  };


  void prepare(double sampleRate, int expectedMaxFramesPerBlock) {
    juce::ignoreUnused(sampleRate, expectedMaxFramesPerBlock);
  }

  float getDistortedSample(const float inputSample) {
    // TODO: either make this a switch or otherwise make it pretty
    if (currentType == DistType::soft) {
      // for the soft tanh function:
      return std::tanh(distK*inputSample);
    }

    else if (currentType == DistType::hard) {
      if (inputSample > tauThresh) {
        return tauThresh;
      } else if (inputSample < (tauThresh - 2 * tauThresh)) {
        return (tauThresh - 2 * tauThresh);
      } else {
        return inputSample;
      }
    } else {
      return inputSample;
    }
  }

  void process(juce::AudioBuffer<float>& buffer) noexcept {
    // for each frame
    for (const auto frameIndex : std::views::iota(0, buffer.getNumSamples())) {

      // for each channel sample in the frame
      for (const auto channelIndex :
           std::views::iota(0, buffer.getNumChannels())) {
        // get the input sample
        const auto inputSample = buffer.getSample(channelIndex, frameIndex);

        auto outputSample = getDistortedSample(inputSample);


        // set the output sample
        buffer.setSample(channelIndex, frameIndex, outputSample);
      }
    }
  }

  void reset() noexcept {}

private:

  // PARAMETERS:
  DistType currentType = DistType::hard;

  float distK = 6.0f; // should be 1-10, maybe 1-15?
  float tauThresh = 0.5f; // -1 to 1 mayhaps?
};
}  // namespace distortion
