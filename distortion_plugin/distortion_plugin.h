/*
==============================================================================

BEGIN_JUCE_MODULE_DECLARATION

   ID:            distortion_plugin
   vendor:        WolfSound
   version:       1.0.0
   name:          distortion Plugin
   description:   Core of the distortion plugin
   dependencies:  juce_audio_utils, juce_dsp

   website:       https://thewolfsound.com
   license:       MIT

END_JUCE_MODULE_DECLARATION

==============================================================================
*/

#pragma once

#include <juce_graphics/juce_graphics.h>
#include <juce_gui_basics/juce_gui_basics.h>
#include <juce_core/juce_core.h>
#include <juce_audio_processors/juce_audio_processors.h>
#include <juce_audio_basics/juce_audio_basics.h>
#include <juce_events/juce_events.h>
#include <juce_dsp/juce_dsp.h>
#include <vector>
#include <memory>
#include <functional>
#include <ranges>
#include <algorithm>
#include <array>
#include <cmath>

#include "include/distortion/Parameters.h"
#include "include/distortion/CustomLookAndFeel.h"
#include "include/distortion/JsonSerializer.h"
#include "include/distortion/distortion.h"
#include "include/distortion/BypassTransitionSmoother.h"
#include "include/distortion/PluginProcessor.h"
#include "include/distortion/PluginEditor.h"
