#include "OgrePyramidsGameState.h"

// Lazy Ogre demo sample framework reuse.
#include "CameraController.h"
#include "GraphicsSystem.h"

#include "OgreSceneManager.h"
#include "OgreManualObject2.h"

#include "OgreCamera.h"
#include "OgreRenderWindow.h"

OgrePyramidsGameState::OgrePyramidsGameState(const Ogre::String &helpDescription)
    : TutorialGameState(helpDescription)
    , mAnimate(false)
{
}


void OgrePyramidsGameState::createScene01(void)
{
    Ogre::SceneManager* sceneManager = mGraphicsSystem->getSceneManager();

    // Create pyramids.
    //TODO: Convert cubes to pyramids.
    Ogre::SceneNode* rootNode = sceneManager->getRootSceneNode(Ogre::SCENE_DYNAMIC);

    mVertices = {
        {1, 0, 0},
        {0, 0, 1},
        {-0.7075, -0.7075, 0},
        {0, 1, 0}
    };

    const size_t gridSize = 500; // animation works
    // const size_t gridSize = 900; // pushing it!
    for (size_t i = 0; i < gridSize; i++)
    {
        for (size_t j = 0; j < gridSize; j++)
        {
            Ogre::ManualObject* manualObject = sceneManager->createManualObject();
            manualObject->estimateVertexCount(4);
            manualObject->estimateIndexCount(12);
            // manualObject->begin("Rocks", Ogre::v1::RenderOperation::OT_TRIANGLE_LIST);
            // manualObject->begin("BaseWhite", Ogre::v1::RenderOperation::OT_TRIANGLE_LIST);
            manualObject->begin("Unlit/Red", Ogre::v1::RenderOperation::OT_TRIANGLE_LIST);
            // manualObject->begin("SimplePbs", Ogre::v1::RenderOperation::OT_TRIANGLE_LIST);

            manualObject->position(mVertices[0]);
            manualObject->normal(0.0f, 1.0f, 0.0f);
            manualObject->tangent(1.0f, 0.0f, 0.0f);
            manualObject->textureCoord(0.0f, 0.0f);

            manualObject->position(mVertices[1]);
            manualObject->normal(0.0f, 1.0f, 0.0f);
            manualObject->tangent(1.0f, 0.0f, 0.0f);
            manualObject->textureCoord(1.0f, 0.0f);

            manualObject->position(mVertices[2]);
            manualObject->normal(0.0f, 1.0f, 0.0f);
            manualObject->tangent(1.0f, 0.0f, 0.0f);
            manualObject->textureCoord(0.0f, 1.0f);

            manualObject->position(mVertices[3]);
            manualObject->normal(0.0f, 1.0f, 0.0f);
            manualObject->tangent(1.0f, 0.0f, 0.0f);
            manualObject->textureCoord(1.0f, 1.0f);

            manualObject->triangle(0, 3, 1);
            manualObject->triangle(1, 3, 2);
            manualObject->triangle(2, 3, 0);
            manualObject->triangle(0, 1, 2);

            manualObject->end();

            Ogre::SceneNode* gridNode = rootNode->createChildSceneNode(Ogre::SCENE_DYNAMIC);
            gridNode->attachObject(manualObject);
            gridNode->scale(1.0f, 1.0f, 1.0f);
            gridNode->setPosition(i, j, 0);

            mSceneNodes.push_back(gridNode);
        }
    }

    Ogre::Light* light = sceneManager->createLight();
    Ogre::SceneNode* lightNode = sceneManager->getRootSceneNode()->createChildSceneNode();
    lightNode->attachObject( light );
    // Since we don't do HDR, counter the PBS' division by PI.
    light->setPowerScale(Ogre::Math::PI);
    light->setType(Ogre::Light::LT_DIRECTIONAL);
    light->setDirection(Ogre::Vector3(-1, -1, -1).normalisedCopy());

    Ogre::Camera* camera = mGraphicsSystem->getCamera();
    camera->setPosition(gridSize / 2.0, 0, 0.8 * gridSize);
    camera->lookAt(gridSize / 2.0, 0.4 * gridSize, 0);
    mCameraController = new Demo::CameraController(mGraphicsSystem, false);

    TutorialGameState::createScene01();
}

void OgrePyramidsGameState::generateDebugText(float timeSinceLast, Ogre::String &outText)
{
    TutorialGameState::generateDebugText(timeSinceLast, outText);

    outText += "\nPress F2 to toggle animation ";
    outText += mAnimate ? "[On]" : "[Off]";

    if (mAnimate)
    {
        std::stringstream ss;
        ss << "\n[currently animating " << mSceneNodes.size() << " pyramids]";
        outText += ss.str();
    }
}

void OgrePyramidsGameState::update(float timeSinceLast)
{
    TutorialGameState::update(timeSinceLast);

    if (mAnimate)
    {
        const float timeQuantum = 0.25;
        mAccumulator += timeSinceLast;
        for (; mAccumulator > timeQuantum; mAccumulator -= timeQuantum)
        {
            for (auto* sceneNode : mSceneNodes)
            {
                sceneNode->yaw(Ogre::Degree(2), Ogre::SceneNode::TS_WORLD);
            }
        }
    }
}

void OgrePyramidsGameState::keyReleased(const SDL_KeyboardEvent &arg)
{
    if( arg.keysym.sym == SDLK_F2 )
    {
        mAnimate = !mAnimate;
    }
    else
    {
        TutorialGameState::keyReleased(arg);
    }
}
