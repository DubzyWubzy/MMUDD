#include "TestUtils.h"
#include <gtest/gtest.h>
#include <distortion_plugin/distortion_plugin.h>

#include <wolfsound/file/wolfsound_WavFileWriter.hpp>
#include <wolfsound/dsp/wolfsound_testSignals.hpp>

namespace distortion {
namespace {
void extractLfo(distortion& distortion, juce::AudioBuffer<float>& bufferToUse) {
  juce::dsp::AudioBlock<float> block{bufferToUse};
  block.fill(1.f);
  distortion.process(bufferToUse);
  block.subtract(1.f);
}
}  // namespace

/** This test extracts the LFO used by the distortion effect and saves it to a WAV
 * file "lfo.wav".
 *
 * You can find the file in the same folder where the test executable resides,
 * most probably [CMake binary dir]/test/.
 *
 * The LFO rate is not changed; thus, the one set in distortion's constructor will
 * be used.
 */
TEST(distortion, ExtractLfo) {
  for (const auto lfoWaveform :
       {distortion::LfoWaveform::sine, distortion::LfoWaveform::triangle}) {
    distortion testee;
    constexpr auto sampleRate = 48000.0;
    testee.setLfoWaveform(lfoWaveform);
    testee.prepare(sampleRate, static_cast<int>(sampleRate));

    juce::AudioBuffer<float> buffer;
    buffer.setSize(1, static_cast<int>(sampleRate));

    extractLfo(testee, buffer);

    const auto* const fileName = lfoWaveform == distortion::LfoWaveform::sine
                                     ? "sineLfo.wav"
                                     : "triangleLfo.wav";

    wolfsound::WavFileWriter::writeToFile(
        getFileOutputPath(fileName),
        juce::Span{buffer.getReadPointer(0),
                   static_cast<size_t>(buffer.getNumSamples())},
        wolfsound::Frequency{sampleRate});
  }
}

/** This test extracts the LFO used by the distortion effect switching the LFO
 * shape mid-processing, and saves it to a WAV file "smoothedLfo.wav".
 *
 * You can find the file in the same folder where the test executable resides,
 * most probably [CMake binary dir]/test/.
 *
 * The LFO rate is not changed; thus, the one set in distortion's constructor will
 * be used.
 */
TEST(distortion, LfoWaveformTransitionIsSmooth) {
  distortion testee;
  constexpr auto sampleRate = 48000.0;
  constexpr auto channelCount = 1;
  constexpr auto blockSizeSeconds = 1;
  constexpr auto blockSizeSamples =
      static_cast<int>(blockSizeSeconds * sampleRate);
  testee.prepare(sampleRate, blockSizeSamples);

  juce::AudioBuffer<float> outputBuffer;
  constexpr auto recordingLengthSamples = 2 * blockSizeSamples;
  outputBuffer.setSize(channelCount, recordingLengthSamples);

  juce::AudioBuffer<float> processBuffer;
  processBuffer.setSize(channelCount, blockSizeSamples);

  testee.setLfoWaveform(distortion::LfoWaveform::sine);
  extractLfo(testee, processBuffer);
  outputBuffer.copyFrom(0, 0, processBuffer, 0, 0, blockSizeSamples);
  testee.setLfoWaveform(distortion::LfoWaveform::triangle);
  extractLfo(testee, processBuffer);
  outputBuffer.copyFrom(0, blockSizeSamples, processBuffer, 0, 0,
                        blockSizeSamples);

  wolfsound::WavFileWriter::writeToFile(
      getFileOutputPath("smoothedLfo.wav"),
      juce::Span{outputBuffer.getReadPointer(0),
                 static_cast<size_t>(outputBuffer.getNumSamples())},
      wolfsound::Frequency{sampleRate});
}
}  // namespace distortion
