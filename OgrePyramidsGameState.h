#ifndef __azdo__OgrePyramidsGameState_h_
#define __azdo__OgrePyramidsGameState_h_

#include "OgrePrerequisites.h"

// Lazy reuse of Ogre Sample framework.
#include "TutorialGameState.h"

class OgrePyramidsGameState : public Demo::TutorialGameState
{
public:
    OgrePyramidsGameState(const Ogre::String &helpDescription);

    virtual void createScene01(void);

    virtual void generateDebugText(float timeSinceLast, Ogre::String &outText) ;

    virtual void update(float timeSinceLast);

    virtual void keyReleased(const SDL_KeyboardEvent & arg);

private:
    std::vector<Ogre::SceneNode*> mSceneNodes;

    std::vector<Ogre::Vector3> mVertices;
    bool mAnimate;
    float mAccumulator;
};

#endif // __azdo__OgrePyramidsGameState_h_
