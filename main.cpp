/*!
 * main.cpp
 * @author Jeffrey Yurkiw
 * @date 2012-02-21
 *
 * Note: In order to properly generate the Doxygen documentation for this
 * project, JavaDoc Autobriefs must be turned on.
*/

#include "OgreFramework.h"
#include "BasicViewportAction.h"
#include "MeshLoader.h"
#include "Ogre.h"

using namespace Ogre;

class TestAction : public OgreAction
{
public:
	Root *root;
	RenderWindow *window;

	SceneManager *pSM;
	SceneNode *pMainNode;

	Camera *pMainCam;
	SceneNode *pMainCamNode;

	Viewport *pVp;

	ManualObject *pMObj;
	String meshName;

	void createMesh(ManualObject*);

	TestAction(OgreFramework *p_para_f) : root(p_para_f->pRoot), window(p_para_f->pWindow)
	{
		String smName = "First SceneManager";
		String sName = "Test Scene";
		String cName = "Test Camera";
		String mOName = "Cube";
		meshName = "MeshCube";

		float width = 0.88f, height = 0.88f;
		float left = (1.0f - width) * 0.5f;
		float top = (1.0f - height) * 0.5f;
		unsigned short mainZOrder = 100;
		float camRatio;

		pSM = root->createSceneManager(ST_GENERIC, smName);
		pMainNode = pSM->getRootSceneNode();

		pMainCam = pSM->createCamera(cName);
		pMainCamNode = pMainNode->createChildSceneNode(cName + " Node");
		pMainCamNode->attachObject(pMainCam);

		pVp = window->addViewport(pMainCam, mainZOrder, left, top, width, height);
		pVp->setAutoUpdated(true);
		pVp->setBackgroundColour(ColourValue(1,0,1));

		camRatio = (float)pVp->getActualWidth() / (float)pVp->getActualHeight();
		pMainCam->setAspectRatio(camRatio);

		pMainCam->setNearClipDistance(1.5f);
		pMainCam->setFarClipDistance(3000.0f);

		window->setActive(true);
		window->setAutoUpdated(false);

		pMObj = pSM->createManualObject(mOName);
		pMObj->setDynamic(false);

		createMesh(pMObj);

		int numEntities = 5;

		for (int iter = 0; iter < numEntities; ++iter)
		{
			Entity *entity = pSM->createEntity(meshName);
			SceneNode *node = pMainNode->createChildSceneNode();
			node->attachObject(entity);
			float offset = float(1+ iter * 2) - (float(numEntities));
			node->translate(offset, offset, -30.0f);
		}

		root->clearEventTimes();
	}

	void createManualObject()
	{
		String mOName = "Cube";

		pMObj = pSM->createManualObject(mOName);
		pMObj->setDynamic(false);

		createMesh(pMObj);

		int numEntities = 5;

		for (int iter = 0; iter < numEntities; ++iter)
		{
			Entity *entity = pSM->createEntity(meshName);
			SceneNode *node = pMainNode->createChildSceneNode();
			node->attachObject(entity);
			float offset = float(1+ iter * 2) - (float(numEntities));
			node->translate(offset, offset, -30.0f);
		}

		root->clearEventTimes();
	}

	void run( void )
	{
		window->update(false);
		window->swapBuffers(true);
		root->renderOneFrame();
	}
};

int main (int argv, char **argc)
{
	float width = 0.88f, height = 0.88f;
	float left = (1.0f - width) * 0.5f;
	float top = (1.0f - height) * 0.5f;

	OgreInitiator oi;
	oi.autoWindow = false;
	oi.configFilename = "";
	oi.customCapacities = "";
	oi.fullscreen = false;
	oi.logFilename = "Ogre_Framework.log";
	oi.pluginsFilename = "";
	oi.sizeX = 800;
	oi.sizeY = 600;
	oi.windowName = "Framework Window";

	oi.windowParams["FSAA"] = "0";
	oi.windowParams["vsync"] = "true";

	OgreFramework ogre(&oi);
	ogre.createWindow(&oi);

	BasicViewportAction bva(&ogre);
	bva.setActionNames("Basic Scene Manager", "Wood Block Scene", "Wood Block Camera");
	bva.setClippingPlaneDimensions(1.5f, 3000.0f);
	bva.setViewportDimensions(height, width, top, left, 100);
	bva.sceneSetup();

	MeshLoader ml("WoodBlockResources", "/home/master/Programming/ogre/OgreFramework/meshes", false);
	ml.loadResourceDirectory();

	//add meshes to scene
	Entity *entity = bva.sceneManager->createEntity("Cube.mesh");
	SceneNode *node = bva.rootSceneNode->createChildSceneNode();
	node->attachObject(entity);
	node->translate(0, 0, -10.0f);

	ogre.runWindow(&bva);

	return 0;
}

//int main (int argv, char **argc)
//{
//	OgreInitiator oi;
//	oi.autoWindow = false;
//	oi.configFilename = "";
//	oi.customCapacities = "";
//	oi.fullscreen = false;
//	oi.logFilename = "Ogre_Framework.log";
//	oi.pluginsFilename = "";
//	oi.sizeX = 800;
//	oi.sizeY = 600;
//	oi.windowName = "Framework Window";
//
//	oi.windowParams["FSAA"] = "0";
//	oi.windowParams["vsync"] = "true";
//
//	OgreFramework ogre(&oi);
//	ogre.createWindow(&oi);
//
//	TestAction ta(&ogre);
//
//	ogre.runWindow(&ta);
//
//	return 0;
//}

void TestAction::createMesh(ManualObject *manualObject)
{
	float lSize = 0.7f;
	manualObject->begin("BaseWhiteNoLighting", Ogre::RenderOperation::OT_TRIANGLE_LIST);
		float cp = 1.0f * lSize ;
		float cm = -1.0f * lSize;

		manualObject->position(cm, cp, cm);// a vertex
		manualObject->colour(Ogre::ColourValue(0.0f,1.0f,0.0f,1.0f));
		manualObject->position(cp, cp, cm);// a vertex
		manualObject->colour(Ogre::ColourValue(1.0f,1.0f,0.0f,1.0f));
		manualObject->position(cp, cm, cm);// a vertex
		manualObject->colour(Ogre::ColourValue(1.0f,0.0f,0.0f,1.0f));
		manualObject->position(cm, cm, cm);// a vertex
		manualObject->colour(Ogre::ColourValue(0.0f,0.0f,0.0f,1.0f));

		manualObject->position(cm, cp, cp);// a vertex
		manualObject->colour(Ogre::ColourValue(0.0f,1.0f,1.0f,1.0f));
		manualObject->position(cp, cp, cp);// a vertex
		manualObject->colour(Ogre::ColourValue(1.0f,1.0f,1.0f,1.0f));
		manualObject->position(cp, cm, cp);// a vertex
		manualObject->colour(Ogre::ColourValue(1.0f,0.0f,1.0f,1.0f));
		manualObject->position(cm, cm, cp);// a vertex
		manualObject->colour(Ogre::ColourValue(0.0f,0.0f,1.0f,1.0f));

		// face behind / front
		manualObject->triangle(0,1,2);
		manualObject->triangle(2,3,0);
		manualObject->triangle(4,6,5);
		manualObject->triangle(6,4,7);

		// face top / down
		manualObject->triangle(0,4,5);
		manualObject->triangle(5,1,0);
		manualObject->triangle(2,6,7);
		manualObject->triangle(7,3,2);

		// face left / right
		manualObject->triangle(0,7,4);
		manualObject->triangle(7,0,3);
		manualObject->triangle(1,5,6);
		manualObject->triangle(6,2,1);
	manualObject->end();

	String resourceGroup = Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME;
	manualObject->convertToMesh(meshName);
}
