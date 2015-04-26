/*
 * DISTRHO 3BandEQ Plugin, based on 3BandEQ by Michael Gruhn
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

#include "DistrhoPlugin3BandEQ.hpp"
#include "DistrhoUI3BandEQ.hpp"

using DGL::Point;

START_NAMESPACE_DISTRHO

namespace Artwork = DistrhoArtwork3BandEQ;

// -----------------------------------------------------------------------

DistrhoUI3BandEQ::DistrhoUI3BandEQ()
    : UI(Artwork::backgroundWidth, Artwork::backgroundHeight),
      fImgBackground(Artwork::backgroundData, Artwork::backgroundWidth, Artwork::backgroundHeight, GL_BGR),
      fAboutWindow(this)
{
    // about
    Image aboutImage(Artwork::aboutData, Artwork::aboutWidth, Artwork::aboutHeight, GL_BGR);
    fAboutWindow.setImage(aboutImage);

    // sliders
    Image sliderImage(Artwork::sliderData, Artwork::sliderWidth, Artwork::sliderHeight);
    Point<int> sliderPosStart(57, 43);
    Point<int> sliderPosEnd(57, 43 + 160);

    // slider Low
    fSliderLow = new ImageSlider(this, sliderImage);
    fSliderLow->setId(DistrhoPlugin3BandEQ::paramLow);
    fSliderLow->setInverted(true);
    fSliderLow->setStartPos(sliderPosStart);
    fSliderLow->setEndPos(sliderPosEnd);
    fSliderLow->setRange(-24.0f, 24.0f);
    fSliderLow->setCallback(this);

    // slider Mid
    sliderPosStart.setX(120);
    sliderPosEnd.setX(120);
    fSliderMid = new ImageSlider(*fSliderLow);
    fSliderMid->setId(DistrhoPlugin3BandEQ::paramMid);
    fSliderMid->setStartPos(sliderPosStart);
    fSliderMid->setEndPos(sliderPosEnd);

    // slider High
    sliderPosStart.setX(183);
    sliderPosEnd.setX(183);
    fSliderHigh = new ImageSlider(*fSliderLow);
    fSliderHigh->setId(DistrhoPlugin3BandEQ::paramHigh);
    fSliderHigh->setStartPos(sliderPosStart);
    fSliderHigh->setEndPos(sliderPosEnd);

    // slider Master
    sliderPosStart.setX(287);
    sliderPosEnd.setX(287);
    fSliderMaster = new ImageSlider(*fSliderLow);
    fSliderMaster->setId(DistrhoPlugin3BandEQ::paramMaster);
    fSliderMaster->setStartPos(sliderPosStart);
    fSliderMaster->setEndPos(sliderPosEnd);

    // knobs
    Image knobImage(Artwork::knobData, Artwork::knobWidth, Artwork::knobHeight);

    // knob Low-Mid
    fKnobLowMid = new ImageKnob(this, knobImage, ImageKnob::Vertical);
    fKnobLowMid->setId(DistrhoPlugin3BandEQ::paramLowMidFreq);
    fKnobLowMid->setAbsolutePos(65, 269);
    fKnobLowMid->setRange(0.0f, 1000.0f);
    fKnobLowMid->setDefault(440.0f);
    fKnobLowMid->setRotationAngle(270);
    fKnobLowMid->setCallback(this);

    // knob Mid-High
    fKnobMidHigh = new ImageKnob(this, knobImage, ImageKnob::Vertical);
    fKnobMidHigh->setId(DistrhoPlugin3BandEQ::paramMidHighFreq);
    fKnobMidHigh->setAbsolutePos(159, 269);
    fKnobMidHigh->setRange(1000.0f, 20000.0f);
    fKnobMidHigh->setDefault(1000.0f);
    fKnobMidHigh->setRotationAngle(270);
    fKnobMidHigh->setCallback(this);

    // about button
    Image aboutImageNormal(Artwork::aboutButtonNormalData, Artwork::aboutButtonNormalWidth, Artwork::aboutButtonNormalHeight);
    Image aboutImageHover(Artwork::aboutButtonHoverData, Artwork::aboutButtonHoverWidth, Artwork::aboutButtonHoverHeight);
    fButtonAbout = new ImageButton(this, aboutImageNormal, aboutImageHover, aboutImageHover);
    fButtonAbout->setAbsolutePos(264, 300);
    fButtonAbout->setCallback(this);

    // set default values
    programLoaded(0);
}

// -----------------------------------------------------------------------
// DSP Callbacks

void DistrhoUI3BandEQ::parameterChanged(uint32_t index, float value)
{
    switch (index)
    {
    case DistrhoPlugin3BandEQ::paramLow:
        fSliderLow->setValue(value);
        break;
    case DistrhoPlugin3BandEQ::paramMid:
        fSliderMid->setValue(value);
        break;
    case DistrhoPlugin3BandEQ::paramHigh:
        fSliderHigh->setValue(value);
        break;
    case DistrhoPlugin3BandEQ::paramMaster:
        fSliderMaster->setValue(value);
        break;
    case DistrhoPlugin3BandEQ::paramLowMidFreq:
        fKnobLowMid->setValue(value);
        break;
    case DistrhoPlugin3BandEQ::paramMidHighFreq:
        fKnobMidHigh->setValue(value);
        break;
    }
}

void DistrhoUI3BandEQ::programLoaded(uint32_t index)
{
    if (index != 0)
        return;

    // Default values
    fSliderLow->setValue(0.0f);
    fSliderMid->setValue(0.0f);
    fSliderHigh->setValue(0.0f);
    fSliderMaster->setValue(0.0f);
    fKnobLowMid->setValue(220.0f);
    fKnobMidHigh->setValue(2000.0f);
}

// -----------------------------------------------------------------------
// Widget Callbacks

void DistrhoUI3BandEQ::imageButtonClicked(ImageButton* button, int)
{
    if (button != fButtonAbout)
        return;

    fAboutWindow.exec();
}

void DistrhoUI3BandEQ::imageKnobDragStarted(ImageKnob* knob)
{
    editParameter(knob->getId(), true);
}

void DistrhoUI3BandEQ::imageKnobDragFinished(ImageKnob* knob)
{
    editParameter(knob->getId(), false);
}

void DistrhoUI3BandEQ::imageKnobValueChanged(ImageKnob* knob, float value)
{
    setParameterValue(knob->getId(), value);
}

void DistrhoUI3BandEQ::imageSliderDragStarted(ImageSlider* slider)
{
    editParameter(slider->getId(), true);
}

void DistrhoUI3BandEQ::imageSliderDragFinished(ImageSlider* slider)
{
    editParameter(slider->getId(), false);
}

void DistrhoUI3BandEQ::imageSliderValueChanged(ImageSlider* slider, float value)
{
    setParameterValue(slider->getId(), value);
}

void DistrhoUI3BandEQ::onDisplay()
{
    fImgBackground.draw();
}

// -----------------------------------------------------------------------

UI* createUI()
{
    return new DistrhoUI3BandEQ();
}

// -----------------------------------------------------------------------

END_NAMESPACE_DISTRHO
