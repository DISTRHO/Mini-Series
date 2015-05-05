/*
 * DISTRHO PingPongPan Plugin, based on PingPongPan by Michael Gruhn
 * Copyright (C) 2012-2015 Filipe Coelho <falktx@falktx.com>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Lesser General Public License for more details.
 *
 * For a full copy of the license see the LICENSE file.
 */

#ifndef DISTRHO_UI_PINGPONGPAN_HPP_INCLUDED
#define DISTRHO_UI_PINGPONGPAN_HPP_INCLUDED

#include "DistrhoUI.hpp"
#include "ImageWidgets.hpp"

#include "DistrhoArtworkPingPongPan.hpp"

START_NAMESPACE_DISTRHO

// -----------------------------------------------------------------------

class DistrhoUIPingPongPan : public UI,
                             public ImageButton::Callback,
                             public ImageKnob::Callback
{
public:
    DistrhoUIPingPongPan();

protected:
    // -------------------------------------------------------------------
    // DSP Callbacks

    void parameterChanged(uint32_t index, float value) override;
    void programLoaded(uint32_t index) override;

    // -------------------------------------------------------------------
    // Widget Callbacks

    void imageButtonClicked(ImageButton* button, int) override;
    void imageKnobDragStarted(ImageKnob* knob) override;
    void imageKnobDragFinished(ImageKnob* knob) override;
    void imageKnobValueChanged(ImageKnob* knob, float value) override;

    void onDisplay() override;

private:
    Image fImgBackground;
    ImageAboutWindow fAboutWindow;

    ScopedPointer<ImageButton> fButtonAbout;
    ScopedPointer<ImageKnob>   fKnobFreq, fKnobWidth;

    DISTRHO_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(DistrhoUIPingPongPan)
};

// -----------------------------------------------------------------------

END_NAMESPACE_DISTRHO

#endif // DISTRHO_UI_PINGPONGPAN_HPP_INCLUDED
