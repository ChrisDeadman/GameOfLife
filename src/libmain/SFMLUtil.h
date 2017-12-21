#ifndef GAMEOFLIFE_SFMLUTIL_H
#define GAMEOFLIFE_SFMLUTIL_H

#include <SFML/Graphics.hpp>

void setColor(Text &text, const Color &color) {
#if (SFML_VERSION_MAJOR > 2) || (SFML_VERSION_MAJOR == 2 && SFML_VERSION_MINOR >= 4)
    text.setFillColor(color);
#else
    text.setColor(color);
#endif
}

#endif //GAMEOFLIFE_SFMLUTIL_H
