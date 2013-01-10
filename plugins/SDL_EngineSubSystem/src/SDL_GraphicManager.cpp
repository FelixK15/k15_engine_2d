#include "SDL_GraphicManager.h"
#include "ConfigFile.h"
#include "Log.h"
#include "SDL_Graphic.h"
#include "SDL_Font.h"
#include "SDL_Window.h"
#include "Resource.h"
#include "Camera.h"

#include "Game.h"

#include "SDL_image\SDL_image.h"
#include "SDL_ttf\SDL_ttf.h"
#include "SDL_gfx\SDL_GfxPrimitives.h"

using namespace K15_Engine;

SDL_Surface *createSurface( U16 w,U16 h )
{
	SDL_Surface *sf = SDL_CreateRGBSurface(SDL_SRCALPHA | SDL_RLEACCEL | SDL_SWSURFACE,w,h,_BPP,0,0,0,0);
	SDL_Surface *newSf = SDL_DisplayFormatAlpha(sf);
	SDL_FreeSurface(sf);
	return newSf;
}

SDL_GraphicManager::SDL_GraphicManager()
{
	m_screenSurface = NULL;
	WRITE_DEBUG("SDL_GraphicManager created.");
}

SDL_GraphicManager::~SDL_GraphicManager()
{
	WRITE_DEBUG("SDL_GraphicManager destroyed.");
}

bool SDL_GraphicManager::initialize()
{
	AbstractGraphicManager::initialize();

	if(IMG_Init(IMG_INIT_PNG) == -1){
		WRITE_CRITICALLOG("Could not initialize SDL_GraphicManager. (" + String(IMG_GetError()) + ")");
		return false;
	}
	SDL_ShowCursor(0);
	WRITE_DEBUG("SDL_image has been initialized.");

	return true;
}

bool SDL_GraphicManager::draw( GraphicPtr graphic,Camera *cam )
{
	if(!graphic->loadedSuccessful()){
		return false;
	}

	SDL_Graphic *sdl_graphic = static_cast<SDL_Graphic*>(graphic.get());
	SDL_Rect graphic_rect;

	int graphic_x,graphic_y,graphic_w,graphic_h,cam_x,cam_y,cam_w,cam_h;

	graphic_x = graphic->getPosition().getX();
	graphic_y = graphic->getPosition().getY();
	graphic_w = graphic->getSize().getWidth();
	graphic_h = graphic->getSize().getHeight();

	cam_x = cam == NULL ? 0 : cam->getPosition().getX();
	cam_y = cam == NULL ? 0 : cam->getPosition().getY();
	cam_w = cam == NULL ? SDL_GetVideoSurface()->w : cam->getSize().getWidth();
	cam_h = cam == NULL ? SDL_GetVideoSurface()->h : cam->getSize().getHeight();

	if(graphic_w + graphic_x > cam_w + cam_x){
		graphic_w -= (graphic_w + graphic_x) - (cam_w + cam_x);
	}

	if(graphic_h + graphic_y > cam_h + cam_y){
		graphic_h -= (graphic_h + graphic_y) - (cam_h + cam_y);
	}

	if(graphic_w < 0 || graphic_h < 0){
		return false;
	}

	graphic_rect.x = graphic_x == graphic->getPosition().getX() ? 0 : graphic_x;
	graphic_rect.y = graphic_y == graphic->getPosition().getY() ? 0 : graphic_y;
	graphic_rect.w = graphic_w;
	graphic_rect.h = graphic_h;

	SDL_Rect relative_graphic_rect = {0,0,0,0};
	SDL_Rect *ptr_relatuve_graphic_rect = &relative_graphic_rect;

	if(cam == NULL){
		ptr_relatuve_graphic_rect = NULL;
	}else{
		relative_graphic_rect.x = (graphic_x - cam_x) + cam->getScreenPosition().getX(); 
		relative_graphic_rect.y = (graphic_y - cam_y) + cam->getScreenPosition().getY();

		//Will get ignored.
 		//relative_graphic_rect.w = cam->getSize().getWidth();
		//relative_graphic_rect.h = cam->getSize().getHeight();
	}

	if(sdl_graphic->isScreenAttached()){
// 		relative_graphic_rect.x = graphic_rect.x + relative_graphic_rect.x;
// 		relative_graphic_rect.y = graphic_rect.y + relative_graphic_rect.y;
	}

	if(SDL_BlitSurface(sdl_graphic->getGraphic(),&graphic_rect,m_screenSurface,ptr_relatuve_graphic_rect) == -1){
		WRITE_CRITICALLOG("Could not draw SDL_Surface (" + String(SDL_GetError()) + ")");
		return false;
	}

	return true;
}

void K15_Engine::SDL_GraphicManager::shutdown()
{
	IMG_Quit();

	WRITE_DEBUG("SDL_image has been shutdown.");
}

GraphicPtr SDL_GraphicManager::createGraphic()
{
	GraphicPtr newGraphic(new SDL_Graphic());

	return newGraphic;
}

GraphicPtr SDL_GraphicManager::createGraphic( const String &resourceName )
{
	Resource *res = myGame->getResourceManager()->getResource(resourceName);

	return createGraphic(res);
}

GraphicPtr SDL_GraphicManager::createGraphic( const Circle& circle, const Position& position,const Color& bordercolor, bool fill )
{
	GraphicPtr newGraphic = createGraphic();

	U32 radius = circle.getRadius();

	SDL_Surface *sdl_circle = createSurface(radius * 2 + 1,radius * 2 + 1);

	U8 result = 0;

	if(fill){
		result = filledCircleColor(sdl_circle,radius,radius,radius,
			SDL_MapRGBA(sdl_circle->format,bordercolor.getR(),bordercolor.getG(),bordercolor.getB(),bordercolor.getA()));
	}else{
		result = circleColor(sdl_circle,radius,radius,radius,
			SDL_MapRGBA(sdl_circle->format,bordercolor.getR(),bordercolor.getG(),bordercolor.getB(),bordercolor.getA()));
	}

	if(result == -1){
		WRITE_ERRORLOG("Circle graphic creation failed. (" + String(SDL_GetError()));
		SDL_FreeSurface(sdl_circle);
	}

	if(!static_cast<SDL_Graphic*>(newGraphic.get())->setGraphic(sdl_circle,true)){
		SDL_FreeSurface(sdl_circle);
	}
	
	newGraphic->setPosition(position);

	return newGraphic;
}

GraphicPtr SDL_GraphicManager::createGraphic( const Line& line, const Position& position, const Color &color )
{
	GraphicPtr newGraphic = createGraphic();

	int w = line.getPos2().getX();
	int h = line.getPos2().getY();

	S16 x,y,x2,y2;

	x = 0;
	y = 0;
	x2 = line.getPos2().getX();
	y2 = line.getPos2().getY();

	SDL_Surface *sdl_line = createSurface(w,h);

	S8 result = thickLineColor(sdl_line,x,y,x2,y2,line.getThickness(),
		SDL_MapRGBA(sdl_line->format,color.getR(),color.getG(),color.getB(),color.getA()));

	if(result == -1){
		WRITE_ERRORLOG("Line graphic creation failed. (" + String(SDL_GetError()));
		SDL_FreeSurface(sdl_line);
	}

	if(!static_cast<SDL_Graphic*>(newGraphic.get())->setGraphic(sdl_line,true)){
		SDL_FreeSurface(sdl_line);
	}

	newGraphic->setPosition(line.getPos1());

	return newGraphic;
}

GraphicPtr K15_Engine::SDL_GraphicManager::createGraphic( const Size& size, const Position &position, const Color& color, bool fill )
{
	GraphicPtr newGraphic = createGraphic();

	SDL_Surface *sdl_rect = createSurface(size.getWidth(),size.getHeight());

	S8 result = 0;

	S16 x,y,x2,y2;

	x = 0;
	y = 0;
	x2 = size.getWidth();
	y2 = size.getHeight();

	if(fill){
		result = SDL_FillRect(sdl_rect,NULL,SDL_MapRGBA(sdl_rect->format,color.getR(),color.getG(),color.getB(),color.getA()));
	}else{
		result = rectangleColor(sdl_rect,x,y,x2 - 1,y2 - 1,SDL_MapRGBA(sdl_rect->format,color.getR(),color.getG(),color.getB(),color.getA()));
	}

	if(result == -1){
		WRITE_ERRORLOG("Rectangle graphic creation failed. (" + String(SDL_GetError()));
		SDL_FreeSurface(sdl_rect);
	}

	if(!static_cast<SDL_Graphic*>(newGraphic.get())->setGraphic(sdl_rect,true,true)){
		SDL_FreeSurface(sdl_rect);
	}

	newGraphic->setPosition(position);

	return newGraphic;
}

GraphicPtr SDL_GraphicManager::createGraphic( const Ellipse& ellipse, const Position& position, const Color& color,bool fill )
{
	GraphicPtr newGraphic = createGraphic();

	SDL_Surface *sdl_ellipse = createSurface(ellipse.getXRadius() * ellipse.getYRadius(),ellipse.getXRadius() * ellipse.getYRadius());

	S8 result = 0;
	
	S16 x,y,xr,yr;

	x = 0;
	y = 0;
	xr = ellipse.getXRadius();
	yr = ellipse.getYRadius();

	if(fill){
		result = filledEllipseColor(sdl_ellipse,xr,yr,xr,yr,SDL_MapRGBA(sdl_ellipse->format,color.getR(),color.getG(),color.getB(),color.getA()));
	}else{
		result = ellipseColor(sdl_ellipse,xr,yr,xr,yr,SDL_MapRGBA(sdl_ellipse->format,color.getR(),color.getG(),color.getB(),color.getA()));
	}

	if(result == -1){
		WRITE_ERRORLOG("Ellipse graphic creation failed. (" + String(SDL_GetError()));
		SDL_FreeSurface(sdl_ellipse);
	}

	if(!static_cast<SDL_Graphic*>(newGraphic.get())->setGraphic(sdl_ellipse,true)){
		SDL_FreeSurface(sdl_ellipse);
	}

	newGraphic->setPosition(position);

	return newGraphic;
}

GraphicPtr SDL_GraphicManager::createGraphic( Resource *resource )
{
	GraphicPtr newGraphic = createGraphic();

	newGraphic->setContent(resource);

	return newGraphic;
}

GraphicPtr SDL_GraphicManager::createGraphic( char character, FontPtr font, const Position& position, const Color& color )
{
	GraphicPtr newGraphic = createGraphic();
	TTF_Font *sdl_font = ((SDL_Font*)font.get())->getFont();
	SDL_Color clr;
	clr.r = color.getR();
	clr.g = color.getG();
	clr.b = color.getB();
	((SDL_Graphic*)newGraphic.get())->setGraphic(TTF_RenderUTF8_Solid(sdl_font,&character,clr),true);

	newGraphic->setAlpha(color.getA());
	newGraphic->setPosition(position);

	return newGraphic;
}

bool SDL_GraphicManager::drawShapedGraphic( const Size& size, const Position& position, const Color& color, bool fill )
{
	GraphicPtr graphic = createGraphic(size,position,color,fill);
	return subscribeGraphic(graphic);
}

AbstractWindow* SDL_GraphicManager::createWindow(int width,int height,int bpp,bool fullscreen,const String& caption)
{
	AbstractWindow *window = new SDL_Window(width,height,bpp,fullscreen,caption);
	window->create();
	m_screenSurface = SDL_GetVideoSurface();

	m_window = window;
	return window;
}