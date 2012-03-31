#include "OgreFramework.h"

OgreFramework::~OgreFramework( void )
{
	delete pWindow;

	pRenderSystem = 0;
	delete pRoot;
}

void OgreFramework::createWindow(OgreInitiator *initiator)
{
	if (ready)
	{
		pWindow = pRoot->createRenderWindow(
			initiator->windowName,
			initiator->sizeX,
			initiator->sizeY,
			initiator->fullscreen,
			&initiator->windowParams);

		LogManager::getSingleton().logMessage("Window " + initiator->windowName + " created!");
	}
	else
	{
		LogManager::getSingleton().logMessage("Not ready...not creating a window.");
	}
}

void OgreFramework::runWindow(OgreAction *action)
{
	if (ready)
	{
		while (!pWindow->isClosed())
		{
			WindowEventUtilities::messagePump();
			action->run();


		}

	}
	else
		LogManager::getSingleton().logMessage("Not ready...not running the window.");
}

void OgreFramework::setupRenderSystems( void )
{
	const RenderSystemList& renderSystemList = pRoot->getAvailableRenderers();

	if (renderSystemList.size() == 0)
	{
		LogManager::getSingleton().logMessage("No render systems found!");
		ready = false;
	}
	else
		pRenderSystem = renderSystemList[0];		//Just snag the first one on the list.

	if (ready)
	{
		pRoot->setRenderSystem(pRenderSystem);
		LogManager::getSingleton().logMessage("Render System Selected: " + pRenderSystem->getName());
	}
}
