#ifndef OGREFRAMEWORK_H_
#define OGREFRAMEWORK_H_

#include "Ogre.h"

using namespace Ogre;

/**
 * Action class used to give the framework something to do in its execution loop. Execution
 * logic should be defined by a descendant.
 */
class OgreAction
{
public:
	bool done;							///< Defaults to false; Set true when logic is complete.

	/**
	 * Constructor. Sets done to false.
	 */
	OgreAction( void ) : done(false) { }

	/**
	 * Virtual destructor. Destructor needs to be implemented by child class.
	 */
	virtual ~OgreAction( void ) { }

	/**
	 * Virtual function run needs to be implemented by child class. Will be
	 * run by the OgreFramework in the runWindow function.
	 */
	virtual void run( void ) = 0;
};

/**
 * A reference class used to initialise the OgreFramework. This class contains
 * all variables needed to initialise OGRE3D. All variables are public so it can
 * be easily extended to initialise a more complex framework.
 */
class OgreInitiator
{
public:
	//Configuration and logging
	String customCapacities;			///< Custom Capacities string.
	String configFilename;				///< Name of the config file we're looking for.
	String pluginsFilename;				///< Name of the plugins file we're looking for.
	String logFilename;					///< Name of the log file we're going to write.

	//Window initialisation
	String windowName;					///< Name of the viewport window.
	int sizeX;							///< Width of the window.
	int sizeY;							///< Height of the window.
	bool fullscreen;					///< Is the window fullscreen?
	bool autoWindow;					///< Do we want to create a window automatically?
	NameValuePairList windowParams; 	///< Window parameters.
};

/**
 * A simple framework class for framing a program that renders information in 3D with the
 * OGRE3D library.
 *
 * @date 2012-03-27
 * @author Jeffrey Yurkiw
 */
class OgreFramework
{
public:
	//ogre variables
	Root *pRoot; 						///< The OGRE3D root object.
	RenderWindow *pWindow;				///< The OGRE3D rendering window.

	RenderSystem *pRenderSystem; 		///< A pointer to the OGRE3D Render System we initiate.

	bool ready; 						///< Are we ready to render?

	/**
	 * Standard constructor. Takes an OgreInitiator object reference.
	 * Calls a function to setup our render system, and then if ready is true
	 * initializes the Ogre Root object.
	 *
	 * @param initiator An OgreInitiator object.
	 */
	OgreFramework(OgreInitiator* initiator) : pRoot(new Root())
	{
		setupRenderSystems();
		if (ready) pRoot->initialise(initiator->autoWindow, initiator->windowName, initiator->customCapacities);
	}

	/**
	 * Destructor. Clears all pointer objects and kills the ogre root.
	 */
	~OgreFramework( void );

	/**
	 * If we're ready, use our root object to attempt to create a RenderWindow.
	 * Utilises information from the OgreInitator.
	 * Logs an error message if ready is false.
	 *
	 * @param initiator An OgreInitiator object.
	 */
	void createWindow(OgreInitiator*);

	/**
	 * If we're ready, run the window logic. This loop includes a message pump.
	 * TODO: Pass an object to this function that has something to run in it.
	 */
	void runWindow(OgreAction*);

private:
	/**
	 * Attempt to set up the render system. This must be performed before we attempt to
	 * create the render window.
	 * <ul>
	 * <li>First, fetch a list of possible render systems from our Ogre Root.</li>
	 * <li>Then check the size of our list. If it's equal to zero log an error message and set ready to false.</li>
	 * <li>If it's greater than zero fetch it into pRenderSystem so we can easily access it later.</li>
	 * <li>Finally, if we're ready, tell the Ogre Root to use the render system we grabbed and log
	 * a message saying we successfully found a render system.</li>
	 * </ul>
	 */
	void setupRenderSystems( void );
};

#endif /* OGREFRAMEWORK_H_ */
