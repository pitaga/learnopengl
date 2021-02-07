#include "DIsplayManager.h"
#include "Display.h"

void DisplayManager::createDisplay()
{
    mDisplay = std::make_shared<Display>();
    mDisplay->setTitle("my first window");
    mDisplay->setDisplayMode(DisplayMode(600, 400));
    mDisplay->create(ContextAttri(4, 6));
}

void DisplayManager::updateDisplay()
{
    if (mDisplay) {
        mDisplay->update();
    }
}

void DisplayManager::closeDisplay()
{
    if (mDisplay) {
        mDisplay->destroy();
    }
}

bool DisplayManager::isRequestClosed()
{
    return mDisplay->isRequestClosed();
}

bool DisplayManager::isKeyPressed(unsigned int keyCode)
{
    return mDisplay->isKeyPressed(keyCode);
}
