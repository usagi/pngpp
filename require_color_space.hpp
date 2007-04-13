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
#ifndef PNGPP_REQUIRE_COLOR_SPACE_HPP_INCLUDED
#define PNGPP_REQUIRE_COLOR_SPACE_HPP_INCLUDED

#include "io_transform.hpp"
#include "rgb_pixel.hpp"
#include "rgba_pixel.hpp"

namespace png
{

    template< typename pixel >
    class require_color_space
        : public io_transform
    {
    public:
        void operator()(io_base& io) const;
    };

    // require_color_space class template specializations
    // for various pixel types

    template<>
    inline void
    require_color_space< rgb_pixel >::operator()(io_base& io) const
    {
        if (io.get_color_type() != color_type_rgb
            || io.get_bit_depth()
               != pixel_traits< rgb_pixel >::get_bit_depth())
        {
            throw error("RGB color space required");
        }
    }

    template<>
    inline void
    require_color_space< rgba_pixel >::operator()(io_base& io) const
    {
        if (io.get_color_type() != color_type_rgba
            || io.get_bit_depth()
               != pixel_traits< rgba_pixel >::get_bit_depth())
        {
            throw error("RGBA color space required");
        }
    }

} // namespace png

#endif // PNGPP_REQUIRE_COLOR_SPACE_HPP_INCLUDED
