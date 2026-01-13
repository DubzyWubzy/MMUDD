#pragma once
#include <string>
#include <juce_core/juce_core.h>

namespace distortion {
inline std::string getFileOutputPath(juce::StringRef fileName) {
  return juce::File::getSpecialLocation(
             juce::File::SpecialLocationType::currentExecutableFile)
      .getParentDirectory()
      .getChildFile(fileName)
      .getFullPathName()
      .toStdString();
}
}  // namespace distortion
