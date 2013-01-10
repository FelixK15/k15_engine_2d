#include "AbstractGraphicManager.h"
#include "IGraphic.h"

#include "AbstractWindow.h"

#include "ConfigFile.h"
#include "Camera.h"
#include "Debug.h"
#include "Log.h"

using namespace K15_Engine;

AbstractGraphicManager::AbstractGraphicManager()
{
	m_window = NULL;
}

AbstractGraphicManager::~AbstractGraphicManager()
{
	SAFE_DELETE(m_window);
}

bool K15_Engine::AbstractGraphicManager::initialize()
{
	if(_CAMERA_ALIGNMENT_HORIZONTAL){
		m_cameraAlignment = ALIGNMENT_HORIZONTAL;
	}else{
		m_cameraAlignment = ALIGNMENT_VERTICAL;
	}

	while(_START_CAMERAS != 0){
		createCamera();
		_START_CAMERAS -= 1;
	}
	
	return true;
}

CameraAlignment AbstractGraphicManager::setCameraAlignment( CameraAlignment alignment )
{
	CameraAlignment oldAlignment = m_cameraAlignment;
	m_cameraAlignment = alignment;

	int amount_cameras = m_cameraList.size();

	if(amount_cameras > 0 && m_window != NULL){
		int w = m_cameraAlignment == ALIGNMENT_HORIZONTAL ? m_window->getSize().getWidth() : m_window->getSize().getWidth() / amount_cameras;
		int h = m_cameraAlignment == ALIGNMENT_HORIZONTAL ? m_window->getSize().getHeight() / amount_cameras : m_window->getSize().getWidth();

		int counter = 0;

		//needs to be reassigned, to make it accessible in the lambda
		CameraAlignment lam_alignment = m_cameraAlignment;
		std::for_each(m_cameraList.begin(),m_cameraList.end(),[&lam_alignment,&counter,&w,&h](Camera* cam){
			cam->setSize(w,h);
			int x = lam_alignment == ALIGNMENT_HORIZONTAL ? 0 : w * counter++;
			int y = lam_alignment == ALIGNMENT_HORIZONTAL ? h * counter++ : 0;
			cam->setScreenPosition(Position(x,y));
		});
	}
	
	return oldAlignment;
}

U32 AbstractGraphicManager::createCamera()
{
	Camera *cam = new Camera(Size(_SCREENWIDTH,_SCREENHEIGHT),Position(0,0));
	m_cameraList.push_back(cam);

	setCameraAlignment(m_cameraAlignment);
	return cam->getID();
}

Camera* AbstractGraphicManager::getCamera( U32 index )
{
	int counter = 0;

	for(CameraList::iterator i = m_cameraList.begin();i != m_cameraList.end();i++){
		if(index == counter++){
			return (*i);
		}
	}

	return NULL;
}

void AbstractGraphicManager::shutdown()
{
	if(m_window){
		m_window->destroy();
	}
}

void AbstractGraphicManager::update()
{
	int amountOfDrawnGraphics = 0;

	m_window->swapBuffers();
	for (CameraList::iterator i = m_cameraList.begin();i != m_cameraList.end();i++){
		GraphicList &graphicOfCamera = (*i)->getGraphics();
		amountOfDrawnGraphics += graphicOfCamera.size();
		for(GraphicList::iterator j = graphicOfCamera.begin();j != graphicOfCamera.end();j++){
			draw((*j),(*i));
		}
		graphicOfCamera.clear();
	}

	Debug::drawAlignedDebugString(StringConverter::toString(amountOfDrawnGraphics) + " graphics drawn.");
}

bool AbstractGraphicManager::subscribeGraphic( GraphicPtr graphic )
{
	bool ret = false;

	if(graphic->loadedSuccessful() || !graphic->isVisible()){
// 		if(graphic->drawOutOfBounds()){
// 			GraphicPtr newGraphic = createGraphic();
// 			newGraphic->copyFrom(static_cast<IResourceable*>(graphic.get()));
// 			m_graphicList.push_back(GraphicCameraAssociator(newGraphic,NULL));
// 		}else{
			for (CameraList::iterator i = m_cameraList.begin(); i != m_cameraList.end() ; i++){
				const Size& cam_size = (*i)->getSize();
				const Position& cam_position = (*i)->getPosition();

				const Size& graphic_size = graphic->getSize();
				const Position& graphic_position = graphic->getPosition();

				if(graphic_position.getX() + graphic_size.getWidth() >= cam_position.getX()){
					if(graphic_position.getX() <= cam_position.getX() + cam_size.getWidth()){
						if(graphic_position.getY() + graphic_size.getHeight() >= cam_position.getY()){
							if(graphic_position.getY() <= cam_position.getY() + cam_size.getHeight()){
								//GraphicPtr newGraphic = createGraphic();
								//newGraphic->copyFrom(static_cast<IResourceable*>(graphic.get()));
								(*i)->addGraphic(graphic);
								ret = true;
						}
					}
				}
			}
		}
	}

	return ret;
}