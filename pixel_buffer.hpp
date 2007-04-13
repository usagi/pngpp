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
#ifndef PNGPP_PIXEL_BUFFER_HPP_INCLUDED
#define PNGPP_PIXEL_BUFFER_HPP_INCLUDED

#include <cstddef>
#include <stdexcept>
#include <vector>

namespace png
{

    template< typename pixel >
    class pixel_buffer
    {
    public:
        typedef std::vector< pixel > row;

        pixel_buffer(void)
            : m_width(0),
              m_height(0)
        {
        }

        pixel_buffer(size_t width, size_t height)
            : m_width(0),
              m_height(0)
        {
            resize(width, height);
        }

        size_t get_width(void) const
        {
            return m_width;
        }

        size_t get_height(void) const
	    {
            return m_height;
	    }

        void resize(size_t width, size_t height)
        {
            m_width = width;
            m_height = height;
            m_rows.resize(height);
            for (typename row_vec::iterator r = m_rows.begin();
                 r != m_rows.end();
                 ++r)
            {
                r->resize(width);
            }
        }

        row& get_row(int index)
        {
            return m_rows.at(index);
        }
        
        row const& get_row(int index) const
        {
            return m_rows.at(index);
        }

        pixel get_pixel(int x, int y) const
        {
            return get_row(y).at(x);
        }

        void set_pixel(int x, int y, pixel p)
        {
            get_row(y).at(x) = p;
        }

    protected:
        size_t m_width;
        size_t m_height;
        typedef std::vector< row > row_vec;
        row_vec m_rows;
    };

} // namespace png

#endif // PNGPP_PIXEL_BUFFER_HPP_INCLUDED
