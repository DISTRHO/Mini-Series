#!/usr/bin/make -f
# Makefile for DISTRHO Plugins #
# ---------------------------- #
# Created by falkTX
#

# --------------------------------------------------------------
# Project name, used for binaries

NAME = PingPongPan

# --------------------------------------------------------------
# Files to build

OBJS_DSP = \
	DistrhoPluginPingPongPan.cpp.o

OBJS_UI  = \
	DistrhoArtworkPingPongPan.cpp.o \
	DistrhoUIPingPongPan.cpp.o

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
