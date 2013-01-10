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
 * Manager Class for Graphics.
 * Graphics gets created via this class.
 *
 * Graphics gets secretly created within the GraphicManagerSubSystem.
 */

#ifndef __GRAPHICMANAGER__
#define __GRAPHICMANAGER__

#include "Color.h"
#include "Size.h"
#include "Circle.h"
#include "Rectangle.h"
#include "Resource.h"
#include "Line.h"
#include "Ellipse.h"

#define DRAW_GRAPHIC(ptr)	myGame->getGraphicManager()->subscribeGraphic(ptr)

namespace K15_Engine
{
	enum CameraAlignment{
		ALIGNMENT_VERTICAL,
		ALIGNMENT_HORIZONTAL
	};

	class GraphicCameraAssociator
	{
	public:
		GraphicCameraAssociator(GraphicPtr ptr,Camera* cam){graphic = ptr, camera = cam;}
		GraphicCameraAssociator(const GraphicCameraAssociator& gca){graphic = gca.graphic;camera = gca.camera;}

		GraphicPtr graphic;
		Camera* camera;
	};

	typedef std::list<GraphicCameraAssociator> GraphicMap;
	typedef std::list<Camera*> CameraList;

	class K15ENGINE_API AbstractGraphicManager
	{

	public:
		
		/**
		* Standard constructor
		*/
		AbstractGraphicManager();

		/**
		* Standard destructor
		*/
		virtual ~AbstractGraphicManager();

		/**
		* Initializes the GraphicManager.
		*
		* @return bool - true if the GraphicManager could be initialized successfully and false if not.
		*/
		virtual bool initialize() = 0;

		/**
		* Shuts the GraphicManager down.
		*/
		virtual void shutdown() = 0;

		/**
		* Creates a new empty graphic.
		*
		* @return GraphicPtr - shared_ptr that points to a IGraphic implementation.
		*/
		virtual GraphicPtr createGraphic() = 0;

		/**
		* Creates a new graphic.
		*
		* @param  resourceName - Name of the resource that shall be loaded
		*
		* @return GraphicPtr - shared_ptr that points to a IGraphic implementation.
		*/
		virtual GraphicPtr createGraphic(const String &resourceName) = 0;

		//Creates a new Graphic based on the given circle object with the given color.
		//If fill is true, the graphic will get filled with the given color.


		/**
		* Creates a new graphic.
		*
		* @param  circle - Circle object from where the informations for building this graphic will get read.
		* @param  position - Position object which holds the informations on where to display the new graphic.
		* @param  color - Color object which holds the information on which color the new graphic should have.
		* @param  fill - determines if the new created shape should get filled or not.
		*
		* @return GraphicPtr - shared_ptr that points to a IGraphic implementation.
		*/
		virtual GraphicPtr createGraphic(const Circle& circle, const Position& position = Position(0,0), const Color& color = Color::Black, bool fill = true) = 0;

		
		/**
		* Creates a new graphic.
		*
		* @param  line - Line object from where the informations for building this graphic will get read.
		* @param  position - Position object which holds the informations on where to display the new graphic.
		* @param  color - Color object which holds the information on which color the new graphic should have.
		*
		* @return GraphicPtr - shared_ptr that points to a IGraphic implementation.
		*/
		virtual GraphicPtr createGraphic(const Line& line, const Position& position = Position(0,0), const Color& color = Color::Black ) = 0;

		/**
		* Creates a new graphic.
		*
		* @param  rect - Rectangle object from where the informations for building this graphic will get read.
		* @param  position - Position object which holds the informations on where to display the new graphic.
		* @param  color - Color object which holds the information on which color the new graphic should have.
		* @param  fill - determines if the new created shape should get filled or not.
		*
		* @return GraphicPtr - shared_ptr that points to a IGraphic implementation.
		*/
		virtual GraphicPtr createGraphic(const Size& size, const Position& position = Position(0,0), const Color& color = Color::Black, bool fill = true) = 0;

		/**
		* Draws a new graphic (only once).
		*
		* @param  rect - Rectangle object from where the informations for building this graphic will get read.
		* @param  position - Position object which holds the informations on where to display the new graphic.
		* @param  color - Color object which holds the information on which color the new graphic should have.
		* @param  fill - determines if the new created shape should get filled or not.
		*
		* @return bool - true if drawing was successful and false if not.
		*/
		virtual bool drawShapedGraphic(const Size& size, const Position& position = Position(0,0), const Color& color = Color::Black, bool fille = true) = 0;

		/**
		* Creates a new graphic.
		*
		* @param  ellipse - Ellipse object from where the informations for building this graphic will get read.
		* @param  position - Position object which holds the informations on where to display the new graphic.
		* @param  color - Color object which holds the information on which color the new graphic should have.
		* @param  fill - determines if the new created shape should get filled or not.
		*
		* @return GraphicPtr - shared_ptr that points to a IGraphic implementation.
		*/
		virtual GraphicPtr createGraphic(const Ellipse& ellipse, const Position& position = Position(0,0), const Color& color = Color::Black, bool fill = true) = 0;

		/**
		* Creates a new graphic.
		*
		* @param  resource - Resource object from which the graphic will get created.
		*
		* @return GraphicPtr - shared_ptr that points to a IGraphic implementation.
		*/
		virtual GraphicPtr createGraphic(Resource *resource) = 0;

		/**
		* Creates a new graphic.
		*
		* @param  character - specific character that shall get visualized
		* @param  font - IFont implementation that holds the font informations
		* @param  position - Position object which holds the informations on where to display the new graphic.
		* @param  color - Color object which holds the information on which color the new graphic should have.
		*
		* @return GraphicPtr - shared_ptr that points to a IGraphic implementation.
		*/
		virtual GraphicPtr createGraphic(char character, FontPtr font, const Position& position,const Color& color) = 0;

		/**
		* Creates a new window. (Method will get called automatically during initialization process)
		*
		*
		* @return BaseWindow - Pointer to a BaseWindow implementation.
		*/
		virtual AbstractWindow *createWindow(int width,int height,int bpp,bool fullscreen,const String& caption) = 0;

		virtual bool draw(GraphicPtr graphic,Camera *camera) = 0;

		/**
		* Subscribes a IGraphic implementation for drawing when update is called.
		*
		* @param  graphic - IGraphic implementation which will eventually get drawn.
		*
		* @return bool - true if graphic got subscriped or not (ATTENTION - SUBSCRIPED, NOT DRAWN!).
		*/
		bool subscribeGraphic(GraphicPtr graphic);

		/**
		* Updates the GraphicManager (Will get called ones per tick)
		* All IGraphic implementations that subscribed for drawing, will get drawn here.
		*/
		void update();

		CameraAlignment setCameraAlignment(CameraAlignment alignment);

		U32 createCamera();

		Camera* getCamera(U32 index);

	protected:

		CameraList m_cameraList;

		//GraphicMap m_graphicList;

		AbstractWindow *m_window;

		CameraAlignment m_cameraAlignment;

	};
}

#endif // __GRAPHICMANAGER__
