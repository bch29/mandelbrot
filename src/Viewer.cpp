#include "Viewer.h"

Viewer::Viewer(int screenWidth, int screenHeight, double startScale, double startX, double startY, double scaleSpeed)
    : screenWidth(screenWidth), screenHeight(screenHeight), scale(startScale), x(startX), y(startY), scaleSpeed(scaleSpeed)
{
}
