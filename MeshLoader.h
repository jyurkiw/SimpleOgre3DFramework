/*
 * MeshLoader.h
 *
 *  Created on: 2012-03-31
 *      Author: master
 */

#ifndef MESHLOADER_H_
#define MESHLOADER_H_

#include "Ogre.h"

using namespace Ogre;

static String FILESYSTEM = "FileSystem";	///< FileSystem string constant

/**
 * Loads a mesh into memory so that Ogre can use it.
 */
class MeshLoader
{
public:
	String resourceGroupName;					///< Name of the resource group to load under
	String resourceDirectoryPath;				///< Path to the resources to load

	bool recursiveSearch;						///< Search recursively when loading resources?

	/**
	 * Construct a new MeshLoader to retrieve data from the given path into the resource group
	 * of the given name with the given recursivity.
	 *
	 * @param rgName Resource Group Name
	 * @param rdPath Resource Directory Path
	 * @param rSearch Recursive Search
	 */
	MeshLoader(String rgName, String rdPath, bool rSearch) :
			resourceGroupName(rgName), resourceDirectoryPath(rdPath), recursiveSearch(rSearch) { }

	/**
	 * Set the resource target variables.
	 *
	 * @param rgName Resource Group Name
	 * @param rdPath Resource Directory Path
	 * @param rSearch Recursive Search
	 */
	void setResourceTarget(String rgName, String rdPath, bool rSearch)
	{
		resourceGroupName = rgName;
		resourceDirectoryPath = rdPath;
		recursiveSearch = rSearch;
	}

	/**
	 * Load resources from the given resourceDirectoryPath into the given resourceGroupName.
	 */
	void loadResourceDirectory()
	{
		ResourceGroupManager& resourceGroupManager = ResourceGroupManager::getSingleton();
		resourceGroupManager.createResourceGroup(resourceGroupName);
		resourceGroupManager.addResourceLocation(resourceDirectoryPath, FILESYSTEM, resourceGroupName, recursiveSearch);
		resourceGroupManager.initialiseResourceGroup(resourceGroupName);
		resourceGroupManager.loadResourceGroup(resourceGroupName);
	}
};

#endif /* MESHLOADER_H_ */
