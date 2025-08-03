/*  ==============================================================================
 *  Created by Fehmi Demiralp(Fedem) on 2025-05-29 GMT
 *  Copyright (C) 2023-2025 Fedem (Fehmi Demiralp) <f.demiralp@gmail.com>
 *
 *  Released under the MIT License
 *  ==============================================================================
 */

/*  Copyright (C) 2023-2025 Fedem (Fehmi Demiralp) <f.demiralp@gmail.com>
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a copy
 *  of this software and associated documentation files (the "Software"), to deal
 *  in the Software without restriction, including without limitation the rights
 *  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *  copies of the Software, and to permit persons to whom the Software is
 *  furnished to do so, subject to the following conditions:
 *
 *  The above copyright notice and this permission notice shall be included in all
 *  copies or substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 *  SOFTWARE.
 */

#include "Display_Utilities.hh"

#include <cstdio>
#include <cstring>

namespace Display_Internal
{
  void GetAccumulatorData( Display_DataType const* const data, char* const accdata, size_t datalen )
  {
    if( accdata != NULL )
    {
      size_t len = 0;
      size_t tlen;
      char* ptr = accdata;

      if( ! data->BaseSignaturePositive )
      {
        *ptr = '-';
        ptr++;
        len++;
      }

      tlen = std::strlen( data->BaseDigits );
      if( tlen > 0 )
      {
        snprintf( ptr, datalen - len, "%s", data->BaseDigits );
        ptr += tlen;
        len += tlen;

        tlen = std::strlen( data->FractionalDigits );
        if( tlen > 0 || data->FractionalStart )
        {
          *ptr = '.';
          ptr++;
          len++;
        }

        if( tlen > 0 )
        {
          snprintf( ptr, datalen - len, "%s", data->FractionalDigits );
          ptr += tlen;
          len += tlen;
        }

        tlen = std::strlen( data->ExponentialDigits );
        if( tlen > 0 || data->ExponentStart )
        {
          *ptr = 'E';
          ptr++;
          len++;

          if( ! data->ExponentialSignaturePositive )
          {
            *ptr = '-';
            ptr++;
            len++;
          }
        }

        if( tlen > 0 )
        {
          snprintf( ptr, datalen - len, "%s", data->ExponentialDigits );
          ptr += tlen;
          len += tlen;
        }
      }
      else
      {
        *ptr = '0';
        ptr++;
        len++;
      }

      *ptr = '\0';
    }
  }
}  // namespace Display_Internal

// End of Display_Utilities.cpp
