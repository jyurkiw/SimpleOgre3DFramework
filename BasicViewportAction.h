/*
 * BasicViewportAction.h
 *
 *  Created on: 2012-03-29
 *      Author: master
 */

#ifndef BASICVIEWPORTACTION_H_
#define BASICVIEWPORTACTION_H_

#import "OgreFramework.h"
#import "Ogre.h"

using namespace Ogre;

class BasicViewportAction : public OgreAction
{
public:
	Root *root;						///< Ogre Root object from the framework.
	RenderWindow *window;			///< Render Window from the framework.

	SceneManager *sceneManager;		///< The primary scene manager (auto-generated).
	SceneNode *rootSceneNode;		///< The root scene node (auto-generated).
	SceneNode *cameraNode;			///< The camera node descended from the root scene node (auto-generated).

	Camera *mainCamera;				///< The main camera object (auto-generated).

	Viewport *viewport;				///< The main viewport (auto-generated).

	String sceneManagerName;		///< The name of the scene manager (set).
	String sceneName;				///< The name of the scene (set).
	String cameraName;				///< The name of the camera (set).

	float viewportWidth;			///< The width of the viewport window.
	float viewportHeight;			///< The height of the viewport window.
	float viewportLeftOffset;		///< The left offset of the viewport window.
	float viewportTopOffset;		///< The top offset of the viewport window.
	unsigned short mainViewportZOrder;	///< The viewport's Z Order.

	bool autoupdate;				///< Set the viewport's autoupdate.
	ColourValue viewportBackgroundColor;	///< Set the viewport's background color.

	float nearClipDistance;			///< Distance of the near clipping plane.
	float farClipDistance;			///< Distance of the far clipping plane.

	/**
	 * Basic Viewport Action constructor. Sets root and window variables from the framework.
	 *
	 * @param pRootFrame An OgreFramework object.
	 */
	BasicViewportAction(OgreFramework *pRootFrame) :
		root(pRootFrame->pRoot), window(pRootFrame->pWindow), sceneManagerName(""), sceneName(""), cameraName(""),
		viewportWidth(0), viewportHeight(0), viewportLeftOffset(0), viewportTopOffset(0),mainViewportZOrder(0),
		autoupdate(true), viewportBackgroundColor(1,0,1), nearClipDistance(0), farClipDistance(0),
		namesAreSet(false), viewportDimensionsAreSet(false)
		{ }

	/**
	 * Basic Viewport Action destructor. Sets all pointers to zero.
	 */
	~BasicViewportAction()
	{
		root = 0;
		window = 0;
		sceneManager = 0;
		rootSceneNode = 0;
		cameraNode = 0;
		mainCamera = 0;
		viewport = 0;
	}

	/**
	 * Sets name public variables.
	 *
	 * @param para_sceneManagerName Scene Manager Name parameter.
	 * @param para_sceneName Scene Name parameter.
	 * @param para_cameraName Camera name parameter.
	 */
	void setActionNames(String para_sceneManagerName, String para_sceneName, String para_cameraName)
	{
		sceneManagerName = para_sceneManagerName;
		sceneName = para_sceneName;
		cameraName = para_cameraName;
		namesAreSet = true;
	}

	/**
	 * Sets viewport dimension variables.
	 *
	 * @param height Height of the viewport window.
	 * @param width Width of the viewport window.
	 * @param top Top offset of the viewport in the window.
	 * @param left Left offset of the viewport in the window.
	 * @param zOrder ZOrder of the viewport.
	 */
	void setViewportDimensions(float height, float width, float top, float left, unsigned short zOrder)
	{
		viewportHeight = height;
		viewportWidth = width;
		viewportTopOffset = top;
		viewportLeftOffset = left;
		mainViewportZOrder = zOrder;
		viewportDimensionsAreSet = true;
	}

	/**
	 * Set clipping plane dimensions.
	 *
	 * @param near Distance of the near clipping plane.
	 * @param far Distance of the far clipping plane.
	 */
	void setClippingPlaneDimensions(float near, float far)
	{
		nearClipDistance = near;
		farClipDistance = far;
	}

	///Set up a basic, empty scene with a camera.
	void sceneSetup()
	{
		if (ready())
		{
			//set up node structure
			sceneManager = root->createSceneManager(ST_GENERIC, sceneManagerName);
			rootSceneNode = sceneManager->getRootSceneNode();
			cameraNode = rootSceneNode->createChildSceneNode(cameraName + "Node");

			//create camera
			mainCamera = sceneManager->createCamera(cameraName);

			//attach camera to camera node
			cameraNode->attachObject(mainCamera);

			//create the viewport
			viewport = window->addViewport(mainCamera, viewportLeftOffset, viewportTopOffset, viewportWidth, viewportHeight);
			viewport->setAutoUpdated(autoupdate);
			viewport->setBackgroundColour(viewportBackgroundColor);

			//calculate the aspect ratio and set it
			cameraAspectRatio = (float)viewport->getActualWidth() / (float)viewport->getActualHeight();
			mainCamera->setAspectRatio(cameraAspectRatio);

			//set clipping plane
			mainCamera->setNearClipDistance(nearClipDistance);
			mainCamera->setFarClipDistance(farClipDistance);

			//activate the window
			window->setActive(true);
			window->setAutoUpdated(autoupdate);
		}
	}

	///Hook into an OgreFramework.
	void run()
	{
		window->update(false);
		window->swapBuffers(true);
		root->renderOneFrame();
	}

	/**
	 * Returns the viewport's aspect ratio.
	 *
	 * @return viewport actual width over actual height.
	 */
	float getAspectRatio()
	{
		return cameraAspectRatio;
	}

	/**
	 * Returns the action's ready status.
	 *
	 * @return ready The action's ready status.
	 */
	bool ready()
	{
		return haveNamesBeenSet() && haveViewportDimensionsBeenSet() && haveClipPlaneDistancesBeenSet();
	}

private:
	bool namesAreSet;				///< Flag that names have been set.
	bool viewportDimensionsAreSet;	///< Viewport dimensions have been set.
	float cameraAspectRatio;		///< Aspect ratio of the viewport camera.

	///Test name variables for contents. Return false if one of them is empty.
	bool haveNamesBeenSet()
	{
		if (namesAreSet)
			return namesAreSet;
		else
			return !(sceneManagerName == "" || sceneName == "" || cameraName == "");
	}

	///Test viewport dimension variables for contents. Return false if one of them is empty.
	bool haveViewportDimensionsBeenSet()
	{
		if (viewportDimensionsAreSet)
			return viewportDimensionsAreSet;
		else
			return !(viewportHeight == 0 || viewportWidth == 0 || viewportLeftOffset == 0 || viewportTopOffset == 0);
	}

	///Test viewport clipping plane variables for contents. Return false if one of them is empty.
	bool haveClipPlaneDistancesBeenSet()
	{
		return !(nearClipDistance == 0 || farClipDistance == 0);
	}
};

#endif /* BASICVIEWPORTACTION_H_ */
