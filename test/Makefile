#
# Copyright (C) 2007   Alex Shulgin
#
# This file is part of png++ the C++ wrapper for libpng.  Png++ is free
# software; the exact copying conditions are as follows:
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are met:
#
# 1. Redistributions of source code must retain the above copyright notice,
# this list of conditions and the following disclaimer.
#
# 2. Redistributions in binary form must reproduce the above copyright
# notice, this list of conditions and the following disclaimer in the
# documentation and/or other materials provided with the distribution.
#
# 3. The name of the author may not be used to endorse or promote products
# derived from this software without specific prior written permission.
#
# THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
# IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
# OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN
# NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
# SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
# TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
# PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
# LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
# NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
# SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
#
ifndef PREFIX
PREFIX := /usr/local
endif

ifndef PNGPP
PNGPP := ..
endif

make_cflags := -Wall $(CFLAGS) -I$(PREFIX)/include -I$(PNGPP)
make_ldflags := $(LDFLAGS) -L$(PREFIX)/lib

ifndef NDEBUG
make_cflags := $(make_cflags) -g
make_ldflags := $(make_ldflags) -g
endif

ifndef LIBPNG_CONFIG
LIBPNG_CONFIG := libpng-config
endif

sources := convert_color_space.cpp \
  generate_gray_packed.cpp \
  read_write_gray_packed.cpp \
  generate_palette.cpp

deps := $(sources:.cpp=.dep)
objects := $(sources:.cpp=.o)
targets := $(sources:.cpp=$(bin_suffix))

all: $(deps) $(targets)

dist-copy-files:
	mkdir $(dist_dir)/test
	cp $(sources) Makefile README *.png $(dist_dir)/test
	mkdir $(dist_dir)/test/cmp
	cp cmp/*.out $(dist_dir)/test/cmp

clean: clean-targets clean-tests-output clean-deps

clean-targets:
	rm -f $(targets) $(objects)

test: all \
  test-convert_color_space \
  test-generate_gray_packed \
  test-read_write_gray_packed \
  test-generate_palette

test-convert_color_space:
	for i in *.png; do \
		for j in RGB RGBA GRAY GA; do \
			for k in 8 16; do \
				out=$$i.$$j.$$k.out; \
				./convert_color_space $$j $$k $$i $$out \
				&& cmp $$out cmp/$$out; \
			done; \
		done; \
	done

test-generate_gray_packed:
	./generate_gray_packed
	for i in 1 2 4; do \
		out=gray_packed_$$i.png.out; \
		cmp $$out cmp/$$out; \
	done

test-read_write_gray_packed:
	for i in 1 2 4; do \
		in=basn0g0$$i.png; \
		out=$$in.out; \
		./read_write_gray_packed $$i $$in $$out \
		&& cmp $$out cmp/$$out; \
	done

test-generate_palette:
	./generate_palette
	for i in 1 2 4 8; do \
		out=palette$$i.png.out; \
		cmp $$out cmp/$$out; \
	done
	cmp palette8_tRNS.png.out cmp/palette8_tRNS.png.out

clean-tests-output:
	rm -f *.out

.PHONY: all dist-copy-files \
  clean clean-targets \
  test test-convert_color_space \
  clean-tests-output \
  clean-deps

%$(bin_suffix): %.o
	g++ -o $@ $< $(make_ldflags) `$(LIBPNG_CONFIG) --ldflags --libs`

%.o: %.cpp
	g++ -c -o $@ $< $(make_cflags) `$(LIBPNG_CONFIG) --cflags`

%.dep: %.cpp
	g++ -M $(CPPFLAGS) $(make_cflags) $< -o- | \
	  sed 's/\($*\)\.o[ :]*/\1.o $@ : /g' > $@

clean-deps:
	rm -f $(deps)

include $(deps)
