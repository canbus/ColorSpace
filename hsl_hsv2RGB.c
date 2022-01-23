#include <stdint.h>
#include <stdio.h>

// refence: https://axonflux.com/handy-rgb-to-hsl-and-rgb-to-hsv-color-model-c
/**
 * @brief
 *
 * @param hue :[0-360]
 * @param saturation :[0-100]
 * @param lightness :[0-100]
 */
uint8_t hsl2rgb(uint16_t hue, uint8_t saturation, uint8_t lightness, uint8_t *red, uint8_t *green,
                uint8_t *blue)
{
    uint16_t hi = (hue / 60) % 6;
    uint16_t C = (100 - abs(2 * lightness - 100)) * saturation / 100;
    uint16_t M = 100 * (lightness - 0.5 * C) / 100;
    uint16_t X = C * (100 - abs((hue * 100 / 60) % 200 - 100)) / 100;

    switch (hi) {
    case 0: /* hue 0~60 */
        *red = C + M;
        *green = X + M;
        *blue = M;
        break;

    case 1: /* hue 60~120 */
        *red = X + M;
        *green = C + M;
        *blue = M;
        break;

    case 2: /* hue 120~180 */
        *red = M;
        *green = C + M;
        *blue = X + M;
        break;

    case 3: /* hue 180~240 */
        *red = M;
        *green = X + M;
        *blue = C + M;
        break;

    case 4: /* hue 240~300 */
        *red = X + M;
        *green = M;
        *blue = C + M;
        break;

    case 5: /* hue 300~360 */
        *red = C + M;
        *green = M;
        *blue = X + M;
        break;

    default:
        return -1;
    }

    *red = *red * 255 / 100;
    *green = *green * 255 / 100;
    *blue = *blue * 255 / 100;

    return 0;
}

#define MAX(x, y) ((x) > (y) ? (x) : (y))
#define MIN(x, y) ((x) > (y) ? (y) : (x))
/**
 * Converts an RGB color value to HSL. Conversion formula
 * adapted from http://en.wikipedia.org/wiki/HSL_color_space.
 * Assumes r, g, and b are contained in the set [0, 255] and
 * returns h, s, and l in the set [0, 1].
 *
 * @param   Number  r       The red color value
 * @param   Number  g       The green color value
 * @param   Number  b       The blue color value
 */
uint8_t rgb2hsl(float r, float g, float b)
{
    r /= 255, g /= 255, b /= 255;
    float max = MAX(MAX(r, g), b), min = MIN(MIN(r, g), b);
    float h, s, l = (max + min) / 2;

    if (max == min) {
        h = s = 0;  // achromatic
    } else {
        float d = max - min;
        s = l > 0.5 ? d / (2 - max - min) : d / (max + min);
        {
            if ((uint32_t)max == (uint32_t)r) {
                h = (g - b) / d + (g < b ? 6 : 0);
            } else if ((uint32_t)max == (uint32_t)g) {
                h = (b - r) / d + 2;
            }
            if ((uint32_t)max == (uint32_t)b) {
                h = (r - g) / d + 4;
            }
        }
        h /= 6;
    }
    h *= 360;
    s *= 100;
    l *= 100;
    printf("%0.0f,%0.0f,%0.0f\n", h, s, l);
}
/**
 * @brief
 *
 * @param hue :[0-360]
 * @param saturation :[0-100]
 * @param value :[0-100]
 */
int8_t hsv2rgb(uint16_t hue, uint8_t saturation, uint8_t value,
                                      uint8_t *red, uint8_t *green, uint8_t *blue)
{
    uint16_t hi = (hue / 60) % 6;
    uint16_t F = 100 * hue / 60 - 100 * hi;
    uint16_t P = value * (100 - saturation) / 100;
    uint16_t Q = value * (10000 - F * saturation) / 10000;
    uint16_t T = value * (10000 - saturation * (100 - F)) / 10000;

    switch (hi) {
        case 0:
            *red   = value;
            *green = T;
            *blue  = P;
            break;

        case 1:
            *red   = Q;
            *green = value;
            *blue  = P;
            break;

        case 2:
            *red   = P;
            *green = value;
            *blue  = T;
            break;

        case 3:
            *red   = P;
            *green = Q;
            *blue  = value;
            break;

        case 4:
            *red   = T;
            *green = P;
            *blue  = value;
            break;

        case 5:
            *red   = value;
            *green = P;
            *blue  = Q;
            break;

        default:
            return -1;
    }

    *red   = *red * 255 / 100;
    *green = *green * 255 / 100;
    *blue  = *blue * 255 / 100;

    return 0;
}
void rgb2hsv(uint16_t red, uint16_t green, uint16_t blue,
                                 uint16_t *h, uint8_t *s, uint8_t *v)
{
    double hue, saturation, value;
    double m_max = MAX(red, MAX(green, blue));
    double m_min = MIN(red, MIN(green, blue));
    double m_delta = m_max - m_min;

    value = m_max / 255.0;

    if (m_delta == 0) {
        hue = 0;
        saturation = 0;
    } else {
        saturation = m_delta / m_max;

        if (red == m_max) {
            hue = (green - blue) / m_delta;
        } else if (green == m_max) {
            hue = 2 + (blue - red) / m_delta;
        } else {
            hue = 4 + (red - green) / m_delta;
        }

        hue = hue * 60;

        if (hue < 0) {
            hue = hue + 360;
        }
    }

    *h = (int)(hue + 0.5);
    *s = (int)(saturation * 100 + 0.5);
    *v = (int)(value * 100 + 0.5);
}
void main()
{
    uint32_t hslrgbTbl[][4] = {
        {0, 0, 0, 0x000000},      {0, 0, 100, 0xFFFFFF},    {0, 100, 50, 0xFF0000},
        {120, 100, 50, 0x00FF00}, {240, 100, 50, 0x0000FF}, {60, 100, 50, 0xFFFF00},
        {180, 100, 50, 0x00FFFF}, {300, 100, 50, 0xFF00FF}, {0, 0, 75, 0xBFBFBF},
        {0, 0, 50, 0x808080},
    };
    uint8_t i;
    for (i = 0; i < sizeof(hslrgbTbl) / (sizeof(uint32_t) * 4); i++) {
        uint8_t r, g, b;
        uint16_t h, s, l;
        h = hslrgbTbl[i][0];
        s = hslrgbTbl[i][1];
        l = hslrgbTbl[i][2];
        hsl2rgb(h, s, l, &r, &g, &b);
        printf("h,s,l:%d,%d,%d => rgb:0x%06X\n", h, s, l, r << 16 | g << 8 | b);
    }
    for (i = 0; i < sizeof(hslrgbTbl) / (sizeof(uint32_t) * 4); i++) {
        uint8_t r, g, b;
        r = 0xFF & hslrgbTbl[i][3] >> 16;
        g = 0xFF & hslrgbTbl[i][3] >> 8;
        b = 0xFF & hslrgbTbl[i][3];
        rgb2hsl(r, g, b);
    }
    for (i = 0; i < sizeof(hslrgbTbl) / (sizeof(uint32_t) * 4); i++) {
        uint8_t r, g, b;
        uint16_t h, s, v;
        h = hslrgbTbl[i][0];
        s = hslrgbTbl[i][1];
        v = hslrgbTbl[i][2];
        hsv2rgb(h, s, v, &r, &g, &b);
        printf("h,s,v:%d,%d,%d => rgb:0x%06X\n", h, s, v, r << 16 | g << 8 | b);
    }
    for (i = 0; i < sizeof(hslrgbTbl) / (sizeof(uint32_t) * 4); i++) {
        uint8_t r, g, b;
        uint16_t h, s, v;
        r = 0xFF & hslrgbTbl[i][3] >> 16;
        g = 0xFF & hslrgbTbl[i][3] >> 8;
        b = 0xFF & hslrgbTbl[i][3];
        rgb2hsv(r, g, b, &h, &s, &v);
        printf("rgb:0x%06X => h,s,v:%d,%d,%d  \n", r << 16 | g << 8 | b, h, s, v);
    }
}