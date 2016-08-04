#include "OgrePyramids.h"

// Reuse OGRE 2.0 sample classes. (Yep, lazy!)
#include "MainEntryPointHelper.h"

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
INT WINAPI WinMainApp(HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT)
#else
    int mainApp()
#endif
{
    //TODO: Fill in help description string.
    OgrePyramidsGameState gameState("Words are words");
    OgrePyramidsGraphicsSystem graphicsSystem(&gameState);

    gameState._notifyGraphicsSystem(&graphicsSystem);

    graphicsSystem.initialize("Ogre Pyramids");

    if (graphicsSystem.getQuit())
    {
        // User cancelled config.
        graphicsSystem.deinitialize();
        return 0;
    }

    Ogre::RenderWindow* renderWindow = graphicsSystem.getRenderWindow();

    graphicsSystem.createScene01();
    graphicsSystem.createScene02();

    Demo::SdlInputHandler* inputHandler = graphicsSystem.getInputHandler();
    inputHandler->setGrabMousePointer(true);
    inputHandler->setMouseVisible(false);

    //TODO: Replace ogre timer with azdo.
    Ogre::Timer timer;
    unsigned long startTime = timer.getMicroseconds();

    double timeSinceLast = 1.0 / 60.0;

    while (not graphicsSystem.getQuit())
    {
        graphicsSystem.beginFrameParallel();
        graphicsSystem.update(static_cast<float>(timeSinceLast));
        graphicsSystem.finishFrameParallel();
        graphicsSystem.finishFrame();

        if (not renderWindow->isVisible())
        {
            // Don't burn CPU cycles when we're minimized.
            Ogre::Threads::Sleep(500);
        }

        unsigned long endTime = timer.getMicroseconds();
        timeSinceLast = (endTime - startTime) / 1000000.0;
        // Prevent from going haywire.
        timeSinceLast = std::min(1.0, timeSinceLast);
        startTime = endTime;
    }

    graphicsSystem.destroyScene();
    graphicsSystem.deinitialize();

    return 0;
}
