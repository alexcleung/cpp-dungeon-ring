/*
* Functions for drawing pictures / art in the terminal :)
*/
#ifndef PICTURES
#define PICTURES

#include <string>

inline std::string padOrTruncate(
    std::string s,
    unsigned int len = 40,
    char pad_char = ' ',
    char mode = 'B') {
    /*
    * Pad the string `s` to length `pad_len`.
    * Mode indicates whether `s` should be on the (L)eft padded, (R)ight padded, or 
    * equally padded on (B)oth sides.
    */
    if (s.size() > len) {
        return s.substr(0, len);
    }

    unsigned int left_pad;
    unsigned int right_pad;
    switch (mode) {
        case 'L':
            left_pad = len - s.size();
            right_pad = 0;
            break;
        case 'R':
            left_pad = 0;
            right_pad = len - s.size();
            break;
        default:
            left_pad = (len - s.size()) / 2;
            right_pad = len - left_pad - s.size();
    }

    return std::string(left_pad, pad_char) + s + std::string(right_pad, pad_char);
}

#endif