#ifndef __azdo__OgrePyramids_h_
#define __azdo__OgrePyramids_h_

// Reuse OGRE 2.0 sample classes. (Yep, lazy!)
#include "GraphicsSystem.h"
#include "OgrePyramidsGameState.h"
#include "SdlInputHandler.h"

#include "OgreTimer.h"
#include "Threading/OgreThreads.h"
#include "OgreRenderWindow.h"
#include "OgreRoot.h"
#include "OgreConfigFile.h"
#include "Compositor/OgreCompositorManager2.h"

class OgrePyramidsGraphicsSystem : public Demo::GraphicsSystem
{
    virtual void setupResources(void)
    {
        Demo::GraphicsSystem::setupResources();

        Ogre::ConfigFile cf;
        cf.load(mResourcePath + "resources2.cfg");

        Ogre::String dataFolder = cf.getSetting(
            "DoNotUseAsResource", "Hlms", "");

        if (dataFolder.empty())
            dataFolder = "./";
        else if (*(dataFolder.end() - 1) != '/')
            dataFolder += "/";

        dataFolder += "2.0/scripts/materials";

        addResourceLocation(dataFolder + "/PbsMaterials", "FileSystem", "General");
        addResourceLocation("./media", "FileSystem", "General");
    }

public:
    OgrePyramidsGraphicsSystem(Demo::GameState* gameState) :
        GraphicsSystem(gameState)
    {
    }
};

class OgrePyramids
{
public:

protected:

private:

};

#endif // __azdo__OgrePyramids_h_
