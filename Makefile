#!/usr/bin/make -f
# Makefile for DISTRHO Plugins #
# ---------------------------- #
# Created by falkTX
#

all: libs plugins gen

# --------------------------------------------------------------

libs:
	$(MAKE) -C libs/dgl

plugins: libs
	$(MAKE) -C plugins/3BandEQ
	$(MAKE) -C plugins/3BandSplitter
	$(MAKE) -C plugins/PingPongPan

gen: plugins libs/lv2_ttl_generator
	@./libs/generate-ttl.sh

libs/lv2_ttl_generator:
	$(MAKE) -C libs/lv2-ttl-generator

# --------------------------------------------------------------

clean:
	$(MAKE) clean -C libs/dgl
	$(MAKE) clean -C libs/lv2-ttl-generator
	$(MAKE) clean -C plugins/3BandEQ
	$(MAKE) clean -C plugins/3BandSplitter
	$(MAKE) clean -C plugins/PingPongPan

# --------------------------------------------------------------

.PHONY: libs plugins
