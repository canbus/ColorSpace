# 色彩模型（color model）和 色彩空间（color space）
本文提到的RGB、HSV、HSL是色彩模型（color model），即一种表示颜色的“方式",而不是色彩空间（color space）

仅靠色彩模型是无法定义色彩的，如RGB中，即使给定了一组分别代表R、G、B的三元数组，由于R、G、B分别对应的原色未知，是无法计算出其代表的颜色的。只有加上了三原色、白点、gamma等参数后，才能表示物理上的色彩、被称作色彩空间，如sRGB、Adobe RGB等

# RGB 的局限性

RGB 是我们接触最多的颜色模型，由三个通道表示一幅图像，分别为红色(R)，绿色(G)和蓝色(B)。这三种颜色的不同组合可以形成几乎所有的其他颜色。

RGB 颜色模型是图像处理中最基本、最常用、面向硬件的颜色模型，比较容易理解。

RGB 颜色模型利用三个颜色分量的线性组合来表示颜色，任何颜色都与这三个分量有关，而且这三个分量是高度相关的，所以连续变换颜色时并不直观，想对图像的颜色进行调整需要更改这三个分量才行

自然环境下获取的图像容易受自然光照、遮挡和阴影等情况的影响，即对亮度比较敏感。而 RGB 颜色模型的三个分量都与亮度密切相关，即只要亮度改变，三个分量都会随之相应地改变，而没有一种更直观的方式来表达

但是人眼对于这三种颜色分量的敏感程度是不一样的，在单色中，人眼对红色最不敏感，蓝色最敏感，所以 RGB 颜色模型是一种均匀性较差的颜色模型。如果颜色的相似性直接用欧氏距离来度量，其结果与人眼视觉会有较大的偏差。对于某一种颜色，我们很难推测出较为精确的三个分量数值来表示。

RGB 颜色模型适合于显示系统，却并不适合于图像处理。

# HSV 颜色模型
HSV模型在1978年由埃尔维·雷·史密斯创立，它是三原色光模式的一种非线性变换,HSV模型通常用于计算机图形应用中

HSV 表达彩色图像的方式由三个部分组成：

Hue（色调、色相）
Saturation（饱和度、色彩纯净度）
Value（明度）

用下面这个圆柱体来表示 HSV 颜色模型，圆柱体的横截面可以看做是一个极坐标系 ，H 用极坐标的极角表示，S 用极坐标的极轴长度表示，V 用圆柱中轴的高度表示

<img src=./img/16.png width=50%>

Hue 用角度度量，取值范围为0～360°，表示色彩信息，即所处的光谱颜色的位置。，表示如下

<img src=./img/17.png width=50%>

颜色圆环上所有的颜色都是光谱上的颜色，从红色开始按逆时针方向旋转，Hue=0 表示红色，Hue=120 表示绿色，Hue=240 表示蓝色等等

在 GRB中 颜色由三个值共同决定，比如黄色为即 (255,255,0)；在HSV中，黄色只由一个值决定，Hue=60即可

HSV 圆柱体的半边横截面（Hue=60）：

<img src=./img/18.png width=50%>

其中水平方向表示饱和度，饱和度表示颜色接近光谱色的程度。饱和度越高，说明颜色越深，越接近光谱色饱和度越低，说明颜色越浅，越接近白色。饱和度为0表示纯白色。取值范围为0～100%，值越大，颜色越饱和

竖直方向表示明度，决定颜色模型中颜色的明暗程度，明度越高，表示颜色越明亮，范围是 0-100%。明度为0表示纯黑色（此时颜色最暗）

通俗理解为：

在Hue一定的情况下，饱和度减小，就是往光谱色中添加白色，光谱色所占的比例也在减小，饱和度减为0，表示光谱色所占的比例为零，导致整个颜色呈现白色。

明度减小，就是往光谱色中添加黑色，光谱色所占的比例也在减小，明度减为0，表示光谱色所占的比例为零，导致整个颜色呈现黑色

HSV 对用户来说是一种比较直观的颜色模型。我们可以很轻松地得到单一颜色，即指定颜色角H，并让V=S=1，然后通过向其中加入黑色和白色来得到我们需要的颜色。增加黑色可以减小V而S不变，同样增加白色可以减小S而V不变。例如，要得到深蓝色，V=0.4 S=1 H=240度。要得到浅蓝色，V=1 S=0.4 H=240度

HSV 的拉伸对比度增强就是对 S 和 V 两个分量进行归一化(min-max normalize)即可，H 保持不变

RGB颜色模型更加面向于工业，而HSV更加面向于用户，大多数做图像识别这一块的都会运用HSV颜色模型，因为HSV颜色模型表达起来更加直观

# HSL 颜色模型
HSL 和 HSV 比较类似。HSL 也有三个分量，hue（色相）、saturation（饱和度）、lightness（亮度）

HSL更好的反映了“饱和度”和“亮度”作为两个独立参数的直觉观念

HSL 中的 L 分量为亮度，亮度为100，表示白色，亮度为0，表示黑色；HSV 中的 V 分量为明度，明度为100，表示光谱色，明度为0，表示黑色

HSL值的范围:hue[0-360],sat[0-100],lightness[0-100]

<img src=./img/19.png width=50%>

提取白色物体时，使用 HSL 更方便，因为 HSV 中的Hue里没有白色，白色需要由S和V共同决定（S=0, V=100）。而在 HSL 中，白色仅由亮度L一个分量决定。所以检测白色时使用 HSL 颜色模型更准确。

[HSL转RGB]<https://www.rapidtables.com/convert/color/hsl-to-rgb.html>

[RGB转HSL]<https://www.rapidtables.com/convert/color/rgb-to-hsl.html>

RGB到HSL转换

<img src=./img/20.png width=50%>

HSL到RGB的转换

给定HSL空间中的 (h,s,l)值定义的一个颜色，带有h在指示色相角度的值域[0, 360]中，分别表示饱和度和亮度的s和l在值域[0, 1]中，相应在RGB空间中的 (r,g,b)三原色，带有分别对应于红色、绿色和蓝色的r,g和b也在值域[0, 1]中，它们可计算为：

首先，如果s= 0，则结果的颜色是非彩色的、或灰色的。在这个特殊情况，r,g和b都等于l。注意h的值在这种情况下是未定义的。

当s≠ 0的时候，可以使用下列过程：

<img src=./img/21.png width=50%>
<img src=./img/22.png width=50%>

# hsl,hsv,rgb互换代码
```c
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
```