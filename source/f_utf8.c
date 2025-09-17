#include <stdio.h>
#include "forge.h"

/*
 UTF-8 encode / decode helpers
 These implementations are intentionally small and dependency free.
 They are defensive: malformed sequences produce U+FFFD (replacement char)
 and advance one byte to avoid infinite loops.
*/

/* Decode a single UTF-8 sequence at text[*pos]. Advances *pos past the
   consumed bytes and returns the Unicode code point (or 0xFFFD on error).
*/
uint32 f_utf8_to_uint32(const char *text, uint *pos)
{
    uint i = *pos;
    unsigned char c = (unsigned char)text[i];
    uint32 codepoint;
    if (c == 0)
        return 0; /* caller typically checks for text[i] != 0 already */
    if (c < 0x80) /* ASCII */
    {
        (*pos) = i + 1;
        return c;
    }
    /* Determine expected length */
    int expected = 0;
    if ((c & 0xE0) == 0xC0)
    {
        expected = 2;
        codepoint = c & 0x1F;
    }
    else if ((c & 0xF0) == 0xE0)
    {
        expected = 3;
        codepoint = c & 0x0F;
    }
    else if ((c & 0xF8) == 0xF0)
    {
        expected = 4;
        codepoint = c & 0x07;
    }
    else /* Invalid leading byte */
    {
        (*pos) = i + 1;
        return 0xFFFD;
    }
    int k;
    for (k = 1; k < expected; ++k)
    {
        unsigned char t = (unsigned char)text[i + k];
        if ((t & 0xC0) != 0x80) /* not a continuation byte */
        {
            (*pos) = i + 1; /* advance one to avoid stall */
            return 0xFFFD;
        }
        codepoint = (codepoint << 6) | (t & 0x3F);
    }
    /* Check for overlong encodings & code point range */
    if ((expected == 2 && codepoint < 0x80) ||
        (expected == 3 && codepoint < 0x800) ||
        (expected == 4 && codepoint < 0x10000) ||
        codepoint > 0x10FFFF ||
        (codepoint >= 0xD800 && codepoint <= 0xDFFF)) /* surrogate range */
    {
        (*pos) = i + 1; /* treat as invalid single byte */
        return 0xFFFD;
    }
    (*pos) = i + expected;
    return codepoint;
}

/* Encode a Unicode code point to UTF-8. Returns number of bytes written
   (1..4) or 0 on invalid input. 'out' must have space for at least 4 bytes. */
uint f_uint32_to_utf8(uint32 codepoint, char *out)
{
    if (codepoint <= 0x7F)
    {
        out[0] = (char)codepoint;
        return 1;
    }
    if (codepoint <= 0x7FF)
    {
        out[0] = (char)(0xC0 | (codepoint >> 6));
        out[1] = (char)(0x80 | (codepoint & 0x3F));
        return 2;
    }
    if (codepoint <= 0xFFFF)
    {
        if (codepoint >= 0xD800 && codepoint <= 0xDFFF) /* surrogate invalid */
            return 0;
        out[0] = (char)(0xE0 | (codepoint >> 12));
        out[1] = (char)(0x80 | ((codepoint >> 6) & 0x3F));
        out[2] = (char)(0x80 | (codepoint & 0x3F));
        return 3;
    }
    if (codepoint <= 0x10FFFF)
    {
        out[0] = (char)(0xF0 | (codepoint >> 18));
        out[1] = (char)(0x80 | ((codepoint >> 12) & 0x3F));
        out[2] = (char)(0x80 | ((codepoint >> 6) & 0x3F));
        out[3] = (char)(0x80 | (codepoint & 0x3F));
        return 4;
    }
    return 0; /* invalid code point */
}
