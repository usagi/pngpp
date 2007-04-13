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
#ifndef PNGPP_CONVERT_COLOR_SPACE_HPP_INCLUDED
#define PNGPP_CONVERT_COLOR_SPACE_HPP_INCLUDED

#include "io_transform.hpp"
#include "rgb_pixel.hpp"
#include "rgba_pixel.hpp"

namespace png
{

    template< typename pixel >
    class convert_color_space
        : public io_transform
    {
    public:
        inline void operator()(io_base& io) const;
    };

    // convert_color_space class template specializations
    // for various pixel types

    template<>
    class convert_color_space< rgb_pixel >
        : public io_transform
    {
    public:
        void operator()(io_base& io) const
        {
            if (io.get_bit_depth() == 16)
            {
#ifdef PNG_READ_16_TO_8_SUPPORTED
                io.set_strip_16();
#else
                throw error("convert_color_space: expected 8-bit data"
                            " but found 16-bit;"
                            " recompile with PNG_READ_16_TO_8_SUPPORTED");
#endif
            }
            if (io.get_color_type() & color_mask_alpha)
            {
#ifdef PNG_READ_STRIP_ALPHA_SUPPORTED
                io.set_strip_alpha();
#else
                throw error("convert_color_space: alpha channel unexpected;"
                            " recompile with PNG_READ_STRIP_ALPHA_SUPPORTED");
#endif
            }
            if (io.get_color_type() == color_type_palette)
            {
#ifdef PNG_READ_EXPAND_SUPPORTED
                io.set_palette_to_rgb();
#else
                throw error("convert_color_space: expected RGB data"
                            " but found indexed colors;"
                            " recompile with PNG_READ_EXPAND_SUPPORTED");
#endif
            }
            else if (io.get_color_type() == color_type_gray
                     || io.get_color_type() == color_type_gray_alpha)
            {
                if (io.get_color_type() == color_type_gray
                    && io.get_bit_depth() < 8)
                {
#ifdef PNG_READ_EXPAND_SUPPORTED
                    io.set_gray_1_2_4_to_8();
#else
                    throw error("convert_color_space: expected RGB data"
                                " but found grayscale (< 8-bit) colors;"
                                " recompile with PNG_READ_EXPAND_SUPPORTED");
#endif
                }
#ifdef PNG_READ_GRAY_TO_RGB_SUPPORTED
                io.set_gray_to_rgb();
#else
                throw error("convert_color_space: expected RGB data"
                            " but found grayscale colors;"
                            " recompile with PNG_READ_GRAY_TO_RGB_SUPPORTED");
#endif
            }
        }
    };

    template<>
    class convert_color_space< rgba_pixel >
        : public io_transform
    {
    public:
        explicit convert_color_space(uint_32 filler = 0xff)
            : m_filler(filler)
        {
        }

        void operator()(io_base& io) const
        {
            if (io.get_bit_depth() == 16)
            {
#ifdef PNG_READ_16_TO_8_SUPPORTED
                io.set_strip_16();
#else
                throw error("convert_color_space: expected 8-bit data"
                            " but found 16-bit;"
                            " recompile with PNG_READ_16_TO_8_SUPPORTED");
#endif
            }
            if (!(io.get_color_type() & color_mask_alpha))
            {
#if defined(PNG_READ_FILLER_SUPPORTED) && !defined(PNG_1_0_X)
                io.set_add_alpha(m_filler, filler_after);
#else
                throw error("convert_color_space: expected alpha channel"
                            " but none found;"
                            " recompile with PNG_READ_FILLER_SUPPORTED"
                            " and be sure to use libpng > 1.0.x");
#endif
            }
            if (io.get_color_type() == color_type_palette)
            {
#ifdef PNG_READ_EXPAND_SUPPORTED
                io.set_palette_to_rgb();
#else
                throw error("convert_color_space: expected RGB data"
                            " but found indexed colors;"
                            " recompile with PNG_READ_EXPAND_SUPPORTED");
#endif
            }
            else if (io.get_color_type() == color_type_gray
                    || io.get_color_type() == color_type_gray_alpha)
            {
                if (io.get_color_type() == color_type_gray
                    && io.get_bit_depth() < 8)
                {
#ifdef PNG_READ_EXPAND_SUPPORTED
                    io.set_gray_1_2_4_to_8();
#else
                    throw error("convert_color_space: expected RGBA data"
                                " but found grayscale (< 8-bit) colors;"
                                " recompile with PNG_READ_EXPAND_SUPPORTED");
#endif
                }
#ifdef PNG_READ_GRAY_TO_RGB_SUPPORTED
                io.set_gray_to_rgb();
#else
                throw error("convert_color_space: expected RGBA data"
                            " but found grayscale colors;"
                            " recompile with PNG_READ_GRAY_TO_RGB_SUPPORTED");
#endif
            }
        }

    private:
        uint_32 m_filler;
    };


} // namespace png

#endif // PNGPP_CONVERT_COLOR_SPACE_HPP_INCLUDED
