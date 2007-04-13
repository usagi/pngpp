/**
 * Copyright (C) 2007   Alex Shulgin
 *
 * This file is part of png++ the C++ wrapper for libpng.  Png++ is free
 * software; the exact copying conditions are as follows:
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright
 * notice, this list of conditions and the following disclaimer in the
 * documentation and/or other materials provided with the distribution.
 *
 * 3. The name of the author may not be used to endorse or promote products
 * derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN
 * NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
 * TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#ifndef PNGPP_INFO_HPP_INCLUDED
#define PNGPP_INFO_HPP_INCLUDED

#include <cassert>
#include "info_base.hpp"

namespace png
{

    class info
        : public info_base
    {
    public:
        explicit info(png_struct* png)
            : info_base(png)
        {
        }

        void read(void)
        {
            png_read_info(m_png, m_info);
        }

        void write(void) const
        {
            png_write_info(m_png, m_info);
        }

        void update(void)
        {
            assert(m_png);
            assert(m_info);
            png_read_update_info(m_png, m_info);
        }

        size_t get_width(void) const
        {
            assert(m_info);
            return m_info->width;
        }
        
        size_t get_height(void) const
        {
            assert(m_info);
            return m_info->height;
        }

        color_type get_color_type(void) const
        {
            assert(m_info);
            return color_type(m_info->color_type);
        }

        int get_bit_depth(void) const
        {
            assert(m_info);
            return m_info->bit_depth;
        }

        struct header
        {
        public:
            explicit header(uint_32 width = 0,
                            uint_32 height = 0,
                            int bit_depth = 0,
                            color_type color = color_type_gray,
                            interlace_type interlace = interlace_none,
                            compression_type compression
                            = compression_type_default,
                            filter_type filter = filter_type_default)
                : width(width),
                  height(height),
                  bit_depth(bit_depth),
                  color(color),
                  interlace(interlace),
                  compression(compression),
                  filter(filter)
            {
            }

            uint_32 width;
            uint_32 height;
            int bit_depth;
            color_type color;
            interlace_type interlace;
            compression_type compression;
            filter_type filter;
        };

        header get_header(void) const
        {
            header hdr;
            get_header(hdr);
            return hdr;
        }

        void get_header(header& hdr) const
        {
            png_get_IHDR(m_png,
                         m_info,
                         & hdr.width,
                         & hdr.height,
                         & hdr.bit_depth,
                         reinterpret_cast< int* >(& hdr.color),
                         reinterpret_cast< int* >(& hdr.interlace),
                         reinterpret_cast< int* >(& hdr.compression),
                         reinterpret_cast< int* >(& hdr.filter));
        }

        void set_header(header const& hdr)
        {
            png_set_IHDR(m_png,
                         m_info,
                         hdr.width,
                         hdr.height,
                         hdr.bit_depth,
                         hdr.color,
                         hdr.interlace,
                         hdr.compression,
                         hdr.filter);
        }
    };

} // namespace png

#endif // PNGPP_INFO_HPP_INCLUDED
