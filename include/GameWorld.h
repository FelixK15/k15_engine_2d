/**
 * @file
 * @author  Felix Klinge <f.klinge15@gmail.com>
 * @version 1.0
 *
 * @section LICENSE
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 3 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details at
 * http://www.gnu.org/copyleft/gpl.html
 *
 * @section DESCRIPTION
 *
 * Class for GameWorld representation.
 * For Creating GameWorld Objects, see GameWorldCreator.
 */

#pragma once

#ifndef __IGAMEWORLD__
#define __IGAMEWORLD__

#include "StandardIncludes.h"
#include "GameWorldLayer.h"
#include "Size.h"

namespace K15_Engine
{
	typedef std::vector<GameWorldLayer> LayerList;

	class K15ENGINE_API GameWorld
	{

	public:

		/**
		* Standard Constructor
		*/
		GameWorld();

		/**
		* Copy Constructor.
		*
		* @param  gameWorld - GameWorld object from which the data will get copied.
		*
		*/
		GameWorld(const GameWorld &gameWorld);

		/**
		* Standard Destructor.
		*
		*/
		~GameWorld();

		/**
		* Returns the name.
		*
		*
		* @return const String& - Name of the GameWorld
		*/
		const String& getName() const;

		//Function for loading resources necessary for this gameworld.
		//virtual bool loadResources() = 0;

		//Function that will get calles before the gameworlds starts.
		//virtual void preStart() = 0;

		//Function will get called within the destructor.
		//virtual void unloadResource() = 0;

		/**
		* Sets the size of the GameWorld
		*
		* @param  width - width value of the new size
		* @param  height - height value of the new size
		*
		*/
		void setSize(int width,int height);

		/**
		* Sets the size of the GameWorld
		*
		* @param  size - Size object from which the width and height values will get read.
		*
		*/
		void setSize(const Size& size);

		/**
		* Function will get called every tick by the GameWorldState
		*
		* @param  deltaTime - Time in milliseconds that has passed between the last and this tick.
		*
		*/
		void update(U32 deltaTime);
	
		/**
		* GameWorldLayers can be added via this function.
		*
		* @param  layer - GameWorldLayer object that shall get added
		*
		* @return int - Position of the added layer.
		*/
		int addLayer(const GameWorldLayer& layer);

		/**
		* Removes a certain layer.
		*
		* @param  name - name of the layer that shall get removed
		*
		* @return bool - true if the deletion was successful or false if not.
		*/
		bool removeLayer(const String& name);

		/**
		* Removes a certain layer.
		*
		* @param  layerPosition - position of the layer that shall get removed
		*
		* @return bool - true if the deletion was successful or false if not.
		*/
		bool removeLayer(U32 layerPosition);

		/**
		* Returns a specific layer identified by the layer ID.
		*
		* @param  layerID - ID of the layer you wanna get. ( < 0 Background Layer, == 0 Collision Layer, > 0 Foreground Layer)
		*
		* @return GameWorldLayer - Valid pointer to a GameWorldLayer object or NULL if layer wasn't found.
		*/
		GameWorldLayer* getLayer(int layerID);

		/**
		* Returns a specific layer identified by the layer name.
		*
		* @param  layerName - name of the layer you wanna get.
		*
		* @return GameWorldLayer - Valid pointer to a GameWorldLayer object or NULL if layer wasn't found.
		*/
		GameWorldLayer* getLayer(const String& layerName);

		/**
		* If you want to know how many layers the gameworld has, call this function.
		*
		* @return int - number of layers.
		*/
		int getLayerCount(){return m_layerList.size();}

		GameWorld &operator=(const GameWorld &gw);

	private:
		/**
		* Helper method for copy constructor and assignment operator.
		*/
		void _copy(const GameWorld &gw);

		int m_collisionLayerIndex;
		Size m_size; // 64 bit
		String m_name; // 8 * size bit
		LayerList m_layerList; 
	};
}

#endif //__ABSTRACTGAMEWORLD__