#!/usr/bin/make -f
# Makefile for DISTRHO Plugins #
# ---------------------------- #
# Created by falkTX
#

# --------------------------------------------------------------
# Project name, used for binaries

NAME = 3BandEQ

# --------------------------------------------------------------
# Files to build

OBJS_DSP = \
	DistrhoPlugin3BandEQ.cpp.o

OBJS_UI  = \
	DistrhoArtwork3BandEQ.cpp.o \
	DistrhoUI3BandEQ.cpp.o

# --------------------------------------------------------------
# Do some magic

include ../Makefile.mk

# --------------------------------------------------------------
# Enable all possible plugin types

ifeq ($(LINUX),true)
all: jack ladspa dssi lv2_sep vst
else
all: ladspa dssi lv2_sep vst
endif

# --------------------------------------------------------------
