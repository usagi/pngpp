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
#ifndef PNGPP_IO_BASE_HPP_INCLUDED
#define PNGPP_IO_BASE_HPP_INCLUDED

#include <cassert>
#include <cstdio>
#include "error.hpp"
#include "info.hpp"
#include "end_info.hpp"

namespace png
{

    class io_base
    {
        io_base(io_base const&);
        io_base& operator=(io_base const&);

    public:
        explicit io_base(png_struct* png)
            : m_png(png),
              m_info(png),
              m_end_info(png)
        {
        }

        ~io_base(void)
        {
            assert(! m_png);
            assert(! m_info.get_png_struct());
            assert(! m_end_info.get_png_struct());
        }

        info& get_info(void)
        {
            return m_info;
        }

        info const& get_info(void) const
        {
            return m_info;
        }

        end_info& get_end_info(void)
        {
            return m_end_info;
        }

        end_info const& get_end_info(void) const
        {
            return m_end_info;
        }

        //////////////////////////////////////////////////////////////////////
        // info accessors
        //
        size_t get_width(void) const
        {
            return m_info.get_width();
        }

        size_t get_height(void) const
        {
            return m_info.get_height();
        }

        color_type get_color_type(void) const
        {
            return m_info.get_color_type();
        }

        int get_bit_depth(void) const
        {
            return m_info.get_bit_depth();
        }

        info::header get_header(void) const
        {
            return m_info.get_header();
        }

        void get_header(info::header& hdr) const
        {
            m_info.get_header(hdr);
        }

        void set_header(info::header const& hdr)
        {
            m_info.set_header(hdr);
        }

        //////////////////////////////////////////////////////////////////////
        // pixel transformations
        // color space transformations
        //
#if defined(PNG_READ_EXPAND_SUPPORTED)
        void set_gray_1_2_4_to_8(void) const
        {
            png_set_gray_1_2_4_to_8(m_png);
        }

        void set_palette_to_rgb(void) const
        {
            png_set_palette_to_rgb(m_png);
        }
#endif

#if defined(PNG_READ_BGR_SUPPORTED) || defined(PNG_WRITE_BGR_SUPPORTED)
        void set_bgr(void) const
        {
            png_set_bgr(m_png);
        }
#endif

#if defined(PNG_READ_GRAY_TO_RGB_SUPPORTED)
        void set_gray_to_rgb(void) const
        {
            png_set_gray_to_rgb(m_png);
        }
#endif

#ifdef PNG_FLOATING_POINT_SUPPORTED
        void set_rgb_to_gray(rgb_to_gray_error_action error_action
                             = rgb_to_gray_silent,
                             double red_weight   = -1.0,
                             double green_weight = -1.0) const
        {
            png_set_rgb_to_gray(m_png, error_action, red_weight, green_weight);
        }
#else
        void set_rgb_to_gray(rgb_to_gray_error_action error_action
                             = rgb_to_gray_silent,
                             fixed_point red_weight   = -1,
                             fixed_point green_weight = -1) const
        {
            png_set_rgb_to_gray_fixed(m_png, error_action,
                                      red_weight, green_weight);
        }
#endif // PNG_FLOATING_POINT_SUPPORTED

        //////////////////////////////////////////////////////////////////////
        // alpha channel transformations
        //
#if defined(PNG_READ_STRIP_ALPHA_SUPPORTED)
        void set_strip_alpha(void) const
        {
            png_set_strip_alpha(m_png);
        }
#endif

#if defined(PNG_READ_SWAP_ALPHA_SUPPORTED) \
    || defined(PNG_WRITE_SWAP_ALPHA_SUPPORTED)
        void set_swap_alpha(void) const
        {
            png_set_swap_alpha(m_png);
        }
#endif

#if defined(PNG_READ_INVERT_ALPHA_SUPPORTED) \
    || defined(PNG_WRITE_INVERT_ALPHA_SUPPORTED)
        void set_invert_alpha(void) const
        {
            png_set_invert_alpha(m_png);
        }
#endif

#if defined(PNG_READ_FILLER_SUPPORTED) || defined(PNG_WRITE_FILLER_SUPPORTED)
        void set_filler(uint_32 filler, filler_type type) const
        {
            png_set_filler(m_png, filler, type);
        }

#if !defined(PNG_1_0_X)
        void set_add_alpha(uint_32 filler, filler_type type) const
        {
            png_set_add_alpha(m_png, filler, type);
        }
#endif
#endif // PNG_READ_FILLER_SUPPORTED || PNG_WRITE_FILLER_SUPPORTED

        //////////////////////////////////////////////////////////////////////
        // byte order and packing transformations
        //
#if defined(PNG_READ_SWAP_SUPPORTED) || defined(PNG_WRITE_SWAP_SUPPORTED)
        void set_swap(void) const
        {
            png_set_swap(m_png);
        }
#endif

#if defined(PNG_READ_PACK_SUPPORTED) || defined(PNG_WRITE_PACK_SUPPORTED)
        void set_packing(void) const
        {
            png_set_packing(m_png);
        }
#endif

#if defined(PNG_READ_PACKSWAP_SUPPORTED) \
    || defined(PNG_WRITE_PACKSWAP_SUPPORTED)
        void set_packswap(void) const
        {
            png_set_packswap(m_png);
        }
#endif

#if defined(PNG_READ_SHIFT_SUPPORTED) || defined(PNG_WRITE_SHIFT_SUPPORTED)
        void set_shift(byte red_bits, byte green_bits, byte blue_bits,
                       byte alpha_bits = 0) const
        {
            if (get_color_type() != color_type_rgb
                || get_color_type() != color_type_rgb_alpha)
            {
                throw error("set_shift: expected RGB or RGBA color type");
            }
            color bits;
            bits.red = red_bits;
            bits.green = green_bits;
            bits.blue = blue_bits;
            bits.alpha = alpha_bits;
            png_set_shift(m_png, & bits);
        }

        void set_shift(byte gray_bits, byte alpha_bits = 0) const
        {
            if (get_color_type() != color_type_gray
                || get_color_type() != color_type_gray_alpha)
            {
                throw error("set_shift: expected Gray or Gray+Alpha color type");
            }
            color bits;
            bits.gray = gray_bits;
            bits.alpha = alpha_bits;
            png_set_shift(m_png, & bits);
        }
#endif // PNG_READ_SHIFT_SUPPORTED || PNG_WRITE_SHIFT_SUPPORTED

#if defined(PNG_READ_INTERLACING_SUPPORTED) \
    || defined(PNG_WRITE_INTERLACING_SUPPORTED)
        int set_interlace_handling(void) const
        {
            return png_set_interlace_handling(m_png);
        }
#endif

#if defined(PNG_READ_INVERT_SUPPORTED) || defined(PNG_WRITE_INVERT_SUPPORTED)
        void set_invert_mono(void) const
        {
            png_set_invert_mono(m_png);
        }
#endif

#if defined(PNG_READ_16_TO_8_SUPPORTED)
        void set_strip_16(void) const
        {
            png_set_strip_16(m_png);
        }
#endif

    protected:
        void* get_io_ptr(void) const
        {
            return png_get_io_ptr(m_png);
        }

        void set_error(char const* message)
        {
            assert(message);
            m_error = message;
        }

        void reset_error(void)
        {
            m_error.clear();
        }

/*
        std::string const& get_error(void) const
        {
            return m_error;
        }
*/

        bool is_error(void) const
        {
            return !m_error.empty();
        }

        void raise_error(void)
        {
            longjmp(m_png->jmpbuf, -1);
        }

        static void raise_error(png_struct* png, char const* message)
        {
            io_base* io = static_cast< io_base* >(png_get_error_ptr(png));
            io->set_error(message);
            longjmp(png->jmpbuf, -1);
        }

        png_struct* m_png;
        info m_info;
        end_info m_end_info;
        std::string m_error;
    };

} // namespace png

#endif // PNGPP_IO_BASE_HPP_INCLUDED
