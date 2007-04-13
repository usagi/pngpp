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
version := 0.1.1

ifndef PREFIX
PREFIX := /usr/local
endif

ifdef MINGW
bin_suffix := .exe
endif

make_cflags := -Wall $(CFLAGS) -I$(PREFIX)/include
make_ldflags := $(LDFLAGS) -L$(PREFIX)/lib

ifndef NDEBUG
make_cflags := $(make_cflags) -g
make_ldflags := $(make_ldflags) -g
endif

ifndef libpng_config
libpng_config := libpng-config
endif

build_files := Makefile
info_files := AUTHORS COPYING INSTALL README TODO
header_files := *.hpp
source_files := pngpptest.cpp
test_files := test/
dist_files := $(build_files) $(info_files) \
  $(header_files) $(source_files) \
  $(test_files)


target_test := pngpptest$(bin_suffix)
targets := $(target_test)

all: $(targets)

install:
	mkdir -p $(PREFIX)/include/png++
	cp *.hpp $(PREFIX)/include/png++

dist:
	tar -zcf png++-$(version).tar.gz --exclude=.svn $(dist_files)

clean:
	rm -f $(targets)

thorough-clean: clean test-clean

test: $(target_test)
	./$(target_test) test/*.png

test-clean:
	rm -f *.png

.PHONY: all install dist clean thorough-clean test test-clean

$(target_test): pngpptest.cpp *.hpp Makefile
	g++ -o $@ $< $(make_cflags) $(make_ldflags) \
	  `$(libpng_config) --cflags --ldflags --libs`
