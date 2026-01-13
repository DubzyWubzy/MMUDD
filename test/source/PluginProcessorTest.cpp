#include <distortion_plugin/distortion_plugin.h>
#include <gtest/gtest.h>

namespace distortion {
/** This test doesn't test anything but shows that you can instantiate and use a
 * plugin processor in test */
TEST(PluginProcessor, PlaceholderTest) {
  PluginProcessor processor{};
}
}  // namespace distortion
