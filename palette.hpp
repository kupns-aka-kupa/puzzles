#ifndef PALETTE_HPP
#define PALETTE_HPP

#include <QPalette>
#include <QRgb>

class Palette : public QPalette
{
public:
    Palette();

    enum Color : QRgb
    {
        Gray = 0x31363b,
        Black = 0x23262a,
        White = 0xeff0f1,
        Red = 0xce4250,
        Orange = 0xf59e16,
        Blue = 0x2980b9,
        Green = 0x268C52,
        Magenta = 0xbd93f9,
        Purple = 0xf676c0
    };

    Q_ENUM(Color);

};

#endif // PALETTE_HPP
