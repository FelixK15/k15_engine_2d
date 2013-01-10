#include "SDL_Graphic.h"
#include "StringConverter.h"
#include "Resource.h"
#include "Log.h"

#include "SDL_image\SDL_image.h"
#include "SDL_gfx\SDL_rotozoom.h"

using namespace K15_Engine;

SDL_Graphic::SDL_Graphic()
	: AbstractGraphic()
{
	m_graphic = NULL;
	m_originalGraphic = NULL;
	m_colorkey = Color::EmptyColor;
}

SDL_Graphic::~SDL_Graphic()
{
	//the original graphic and the actual graphic will get deleted here.
	if(m_originalGraphic){
		SDL_FreeSurface(m_originalGraphic);
		m_originalGraphic = NULL;
	}

	if(m_graphic){
		SDL_FreeSurface(m_graphic);
		m_graphic = NULL;
	}
}

void SDL_Graphic::unlock()
{
	//SDL Unlock Functions gets called here.
	if(SDL_MUSTLOCK(m_graphic)){
		SDL_UnlockSurface(m_graphic);
		m_locked = true;
	}
}

void SDL_Graphic::lock()
{
	if(m_locked){
		SDL_LockSurface(m_graphic);
	}	
}

bool SDL_Graphic::rotate( F32 angle )
{
	if(!m_graphic){
		WRITE_ERRORLOG("Graphic is empty.");
		return false;
	}

	return setGraphic(rotozoomSurface(m_originalGraphic,angle,1,1),true);
}

bool SDL_Graphic::zoom( F32 zoomX,F32 zoomY )
{
	if(!m_graphic){
		WRITE_ERRORLOG("Graphic is empty.");
		return false;
	}

	return setGraphic(zoomSurface(m_originalGraphic,zoomX,zoomY,0),true);
}

bool SDL_Graphic::shrink( U16 shrinkX,U16 shrinkY )
{
	if(!m_graphic){
		WRITE_ERRORLOG("Graphic is empty.");
		return false;
	}
	
	return setGraphic(shrinkSurface(m_originalGraphic,shrinkX,shrinkY),true);
}

bool SDL_Graphic::fillWithColor( const Color &color )
{
	//It makes no sense to process any further if there's no graphic we can fill.
	if(!m_graphic){
		WRITE_ERRORLOG("Graphic is empty.");
		return false;
	}

	int w,h,bpp;
	w = m_graphic->w;
	h = m_graphic->h;
	bpp = m_graphic->format->BitsPerPixel;

	//New overlay will get created (This will be the overlay we draw the color on)
	SDL_Surface *overlay = SDL_CreateRGBSurface(SDL_SWSURFACE | SDL_SRCCOLORKEY | SDL_SRCALPHA | SDL_RLEACCEL,w,h,bpp,0,0,0,0);
	SDL_Rect fillRect = {0,0,w,h};

	//Error checking if SDL was able to create a new SDL_Surface.
	if(overlay == NULL){
		WRITE_ERRORLOG("Could not create colored overlay. (" + String(SDL_GetError()) + ")");
		return false;
	}

	//colorkey for the overlay (sorry for noobish magic numbers)
	U32 colorkey_overlay = SDL_MapRGB(overlay->format,7,8,9);

	//Overlay will get filled with the colorkey color)
	SDL_FillRect(overlay,&fillRect,colorkey_overlay);

	//Color key gets set. The overlay is totally transparent now.
	SDL_SetColorKey(overlay,SDL_SRCCOLORKEY | SDL_RLEACCEL,colorkey_overlay);

	//each pixel of the overlay will get painted in the Color objects color. (weird sentence).
	//Unfortunately this is the only way in SDL to archive a totally colored AND transparent rectangle.
	U32 color_SDL = SDL_MapRGB(overlay->format,color.getR(),color.getG(),color.getB());
	U32 *pixels = static_cast<U32*>(overlay->pixels);

	for(int x = 0;x < w;x++){
		for(int y = 0;y < h;y++){
			if(getPixel(Position(x,y)) != m_colorkey){
				pixels[x + (y * w)] = color_SDL;
			}
		}
	}

	//Try to set the alpha of the overlay.
 	if(SDL_SetAlpha(overlay,SDL_SRCALPHA | SDL_RLEACCEL,color.getA()) == -1){
 		SDL_FreeSurface(overlay);
 		WRITE_ERRORLOG("Could not set alpha value of colored overlay. (" + String(SDL_GetError()) + ")");
 		return false;
 	}
	
	//Try to blit the overlay onto the graphic.
	if(SDL_BlitSurface(overlay,NULL,m_graphic,NULL) == -1){
		SDL_FreeSurface(overlay);
		WRITE_ERRORLOG("Could not set blit colored overlay. (" + String(SDL_GetError()) + ")");
		return false;
	}

	//if everything worked, the overlay isn't used anymore and hence will get deleted.
	SDL_FreeSurface(overlay);

	return true;
}

bool SDL_Graphic::setColorkey( U8 r,U8 g,U8 b )
{
	//It makes no sense to process any further if there's no graphic we can put a colorkey on.
	if(!m_graphic){
		//WRITE_ERRORLOG("Graphic is empty.");
		return false;
	}

	//flag ,that the graphic has a colorkey will get set.
	m_hasColorkey = true;
	m_colorkey = Color(r,g,b);

	//returns the result of the SetColorKey function from SDL.
// 	for(int x = 0;x < m_size.getWidth();x++){
// 		for(int y = 0;y < m_size.getHeight();y++){
// 			if(getPixel(Position(x,y)) == Color(r,g,b)){
// 				setPixel(Position(x,y),Color::Transparent);
// 			}
// 		}
// 	}

	return SDL_SetColorKey(m_graphic,SDL_SRCCOLORKEY,SDL_MapRGB(m_graphic->format,r,g,b)) == -1 ? false : true;
}

bool SDL_Graphic::setColorkey( const Color &colorkey )
{
	return setColorkey(colorkey.getR(),colorkey.getG(),colorkey.getB());
}

bool SDL_Graphic::setAlpha( U8 alphaValue )
{
	//It makes no sense to process any further if there's no graphic we can transpire
	if(!m_graphic){
		WRITE_ERRORLOG("Graphic is empty.");
		return false;
	}
	
	m_alphaValue = alphaValue;

	SDL_SetAlpha(m_graphic,SDL_SRCALPHA | SDL_RLEACCEL,alphaValue);

	//Check if alphaValue is greater then 0.
	//Alphavalue = 0 means that the graphic is fully transparent
	// (that again means that we can set the visible flag to true)
	if(alphaValue > 0)
		m_visible = true;
	else
		m_visible = false;

	return true;
}

const Color SDL_Graphic::getPixel( const Position &position)
{
	//It makes no sense to process any further if there's no graphic we can retrieve pixels from.
	if(!m_graphic){
		WRITE_ERRORLOG("Graphic is empty.");
		return Color::EmptyColor;
	}

	
	U32 *pixels = (U32 *)m_graphic->pixels;
	int pixelposition = (position.getY() * m_graphic->w) + position.getX();

	//Is the desired pixel within the graphic?
	if( pixelposition > (m_graphic->w * m_graphic->h)){
		return Color::EmptyColor;
	}
	
	U8 r,g,b,a;
	
	//Graphic must be locked before direct pixel access.
	lock();

	//Pixeldata gets read here.
	SDL_GetRGBA(pixels[pixelposition],m_graphic->format,&r,&g,&b,&a);

	//Graphic gets unlocked.
	unlock();

	return Color(r,g,b,a);
}

void SDL_Graphic::restoreOriginal()
{
	//It makes no sense to process any further if there's no originalgraphic we can restore.
	if(!m_originalGraphic){
		WRITE_ERRORLOG("No graphic has been set yet.");
		return;
	}

	if(!m_graphic){
		//Old graphic gets deleted.
		SDL_FreeSurface(m_graphic);
		m_graphic = NULL;

		//New surface gets created with the same size as the original graphic.
		m_graphic = SDL_CreateRGBSurface(SDL_SWSURFACE | SDL_SRCCOLORKEY | SDL_SRCALPHA | SDL_RLEACCEL,
			m_originalGraphic->w,m_originalGraphic->h,m_originalGraphic->format->BitsPerPixel,0,0,0,0);
	}
	
	//original graphic will get blit onto the just created surface.
	SDL_BlitSurface(m_originalGraphic,NULL,m_graphic,NULL);

	m_size = Size(m_originalGraphic->w,m_originalGraphic->h);
	return;
}

bool SDL_Graphic::setPixel(const Position &position,const Color &pixel)
{
	if(!m_graphic){
		WRITE_ERRORLOG("Graphic is empty.");
		return false;
	}

	if(pixel.isEmpty()){
		WRITE_ERRORLOG("Given pixel is empty.");
		return false;
	}

	U32 *pixels = (U32 *)m_graphic->pixels;
	int pixelposition = (position.getY() * m_graphic->w) + position.getX();

	//Is the desired position within the graphic?
	if(pixelposition > (m_graphic->w * m_graphic->h)){
		WRITE_ERRORLOG("Given position is out of bound.");
		return false;
	}

	//graphic must be locked before direct pixel access.
	lock();

	//pixel data gets set here.
	pixels[pixelposition] = SDL_MapRGBA(m_graphic->format,pixel.getR(),pixel.getG(),pixel.getB(),pixel.getA());

	//direct pixel access is done - graphic can get unlocked.
	unlock();

	return true;
}

GraphicPtr SDL_Graphic::cutRect( const Position &position,const Size &size  )
{
	if(!loadedSuccessful()){
		WRITE_ERRORLOG("Can't cut Rect out of an empty graphic.");
		return NULL;
	}

	int w = size.getWidth();
	int h = size.getHeight();
	int x = position.getX();
	int y = position.getY();

	int bpp = m_graphic->format->BitsPerPixel;

	if((x + w) > m_graphic->w){
		if(x > m_graphic->w){
			x = 0;
			w = 0;
		}else{
			w = m_graphic->w - x;
		}
	}

	if((y + h) > m_graphic->h){
		if(y > m_graphic->h){
			y = 0;
			h = 0;
		}else{
			h = m_graphic->h - y;
		}
	}

	//New surface with the size of the cutting rect gets created.
	SDL_Surface *tmpNewSurface = SDL_CreateRGBSurface(SDL_HWSURFACE | SDL_SRCCOLORKEY | SDL_SRCALPHA | SDL_RLEACCEL,
		w,h,bpp,m_originalGraphic->format->Rmask,m_originalGraphic->format->Gmask,m_originalGraphic->format->Bmask,
		m_originalGraphic->format->Amask);

	//If the creation failed, the error will get saved into the log file.
	if(!tmpNewSurface){
		WRITE_ERRORLOG(SDL_GetError());
		return NULL;
	}

	//Format conversion
	SDL_Surface *newSurface = SDL_DisplayFormat(tmpNewSurface);
	SDL_FreeSurface(tmpNewSurface);

	SDL_Rect sdl_cuttingRect;

	sdl_cuttingRect.x = x;
	sdl_cuttingRect.y = y;
	sdl_cuttingRect.w = w;
	sdl_cuttingRect.h = h;

	//A rect with the size of the cutting rect will get blit from the graphic (the original graphic) to the just created surface
	if(SDL_BlitSurface(m_originalGraphic,&sdl_cuttingRect,newSurface,NULL) == -1){

		if(newSurface != NULL){
			SDL_FreeSurface(newSurface);
			newSurface = NULL;
		}

		return NULL;
	}
	
	//time to wrap the newly created surface into the related object.
	GraphicPtr newGraphic = GraphicPtr(new SDL_Graphic());
	SDL_Graphic *newSDLGraphic = static_cast<SDL_Graphic*>(newGraphic.get());
	newSDLGraphic->setGraphic(newSurface,true,true);
	newSDLGraphic->setVisible(m_visible);
	newSDLGraphic->setSize(w,h);

	if(m_hasColorkey){
		newSDLGraphic->setColorkey(m_colorkey);
	}

	return newGraphic;
}

bool SDL_Graphic::copyFrom(IResourceable *resourceable)
{
	if(!resourceable){
		WRITE_ERRORLOG("Graphic is empty.");
		return false;
	}

	SDL_Graphic *otherGraphic = static_cast<SDL_Graphic*>(resourceable);

	m_position = otherGraphic->getPosition();
	m_size = otherGraphic->getSize();

	return setGraphic(otherGraphic->m_graphic,false,true);
}

void SDL_Graphic::setSize( const Size &size )
{
	AbstractGraphic::setSize(size);

	float diffX = static_cast<float>(m_originalGraphic->w / size.getWidth());
	float diffY = static_cast<float>(m_originalGraphic->h / size.getHeight());

	if(diffX == 0){
		diffX = 1;
	}

	if(diffY == 0){
		diffY = 1;
	}

	if(diffX > 0 || diffX > 0){
		zoom(diffX,diffY);
	}else if(diffX < 0 || diffY < 0){
		diffX *= -1;
		diffY *= -1;
		shrink(static_cast<int>(diffX),static_cast<int>(diffY));
	}


}

bool SDL_Graphic::setContent( Resource *resource)
{
	//If the given resource is empty its useless to continue any further.
	if(resource == NULL){
		WRITE_ERRORLOG("Given resource is empty.");
		return false;
	}

	//SDL_RWFromMem creates a SDL_RW struct which holds data from the memory (in this case, the resource).
	//IMG_LOAD_RW takes a SDL_RW struct and creates a SDL_Surface from it.
	//The true parameter of IMG_LOAD_RW controls the deletion of the SDL_RW object.
	if(!setGraphic(IMG_Load_RW(SDL_RWFromMem((void*)resource->getContent(),resource->getSize()),1),true,true)){
		WRITE_ERRORLOG("SDL_RWops could be generated, but image creation failed. (" + String(IMG_GetError()) + ") Resource: " + resource->getName());
		return false;
	}

	return _fitSize();
}

//Private Functions

bool SDL_Graphic::setGraphic( SDL_Surface *newSurface,bool eraseSrcSurface,bool onOriginalGraphic )
{
	if(!newSurface)
		return false;

	SDL_Surface *graphic = NULL;

	if(onOriginalGraphic){
		graphic = m_originalGraphic;
	}else{
		graphic = m_graphic;
	}

	if(graphic){
		SDL_FreeSurface(graphic);
		graphic = NULL;
	}

	if(!SDL_GetVideoSurface())
		graphic = newSurface;
	else{
		graphic = SDL_DisplayFormat(newSurface);
		if(eraseSrcSurface)
			SDL_FreeSurface(newSurface);
	}

// 	if(m_colorkey != Color::EmptyColor){
// 		//m_hasColorkey = true;
// 		setColorkey(m_colorkey);
// 	}

	m_size = Size(graphic->w,graphic->h);

	if(onOriginalGraphic){
		m_originalGraphic = graphic;
	}else{
		m_graphic = graphic;
	}

	if(onOriginalGraphic){
		restoreOriginal();
	}
	

	return true;
}

bool SDL_Graphic::drawAt( GraphicPtr graphic,const Position& position )
{
	if(graphic == NULL || !loadedSuccessful()){
		return false;
	}

	int newWidth = getSize().getWidth();
	int newHeight = getSize().getHeight();

	SDL_Graphic* otherGraphic = static_cast<SDL_Graphic*>(graphic.get());
	SDL_Surface* otherGraphicsSurface = otherGraphic->getGraphic();

	SDL_Rect blitRect;
	blitRect.x = position.getX();
	blitRect.y = position.getY();
	blitRect.w = otherGraphic->getSize().getWidth();
	blitRect.h = otherGraphic->getSize().getHeight();

	if(getSize().getWidth() < graphic->getPosition().getX() + graphic->getSize().getWidth()){
		newWidth = getSize().getWidth() + graphic->getPosition().getX() + graphic->getSize().getWidth();
	}

	if(getSize().getHeight() < graphic->getPosition().getY() + graphic->getSize().getWidth()){
		newHeight = getSize().getHeight() + graphic->getPosition().getY() + graphic->getSize().getHeight();
	}
	
	if(newWidth > getSize().getHeight() || newHeight > getSize().getHeight()){
		SDL_Surface *newSurface = SDL_CreateRGBSurface(SDL_SWSURFACE | SDL_SRCCOLORKEY | SDL_SRCALPHA | SDL_RLEACCEL,newWidth,newHeight,_BPP,m_graphic->format->Rmask,m_graphic->format->Gmask,m_graphic->format->Bmask,m_graphic->format->Amask);
		setGraphic(newSurface,true);
	}

	if(SDL_BlitSurface(otherGraphicsSurface,NULL,m_graphic,&blitRect) == -1){
		WRITE_ERRORLOG(SDL_GetError());
		return false;
	}
	
	return true;
}

void SDL_Graphic::setGraphicAsOrigin()
{
	if(!loadedSuccessful()){
		return;
	}

	setGraphic(m_graphic,false,true);
}

bool SDL_Graphic::_fitSize()
{
	if(!loadedSuccessful()){
		return false;
	}

	if(m_hasColorkey == true){
		U32 *pixels = (U32*) m_graphic->pixels;
		SDL_Rect cutRect;
		cutRect.y = cutRect.x = cutRect.w = cutRect.h = 0;

		for(int y = 0;y < m_graphic->h;++y){
			for(int x = 0;x < m_graphic->w;++x){
				if(pixels[(y * m_graphic->h) + x] != m_graphic->format->colorkey){
					cutRect.y = y;
					break;
				}
			}
			if(cutRect.y > 0)
				break;
		}

		for(int x = 0;x < m_graphic->w;++x){
			for(int y = 0;y < m_graphic->h;++y){
				if(pixels[(y * m_graphic->h) + x] != m_graphic->format->colorkey){
					cutRect.x = x;
					break;
				}
			}
			if(cutRect.x > 0)
				break;
		}

		for(int x = m_graphic->w;x > 0;++x){
			for(int y = m_graphic->h;y > 0;++y){
				if(pixels[(y * m_graphic->h) + x] != m_graphic->format->colorkey){
					cutRect.w = x - cutRect.x;
					break;
				}
			}
			if(cutRect.w > 0)
				break;
		}

		for(int y = m_graphic->h;y > 0;++y){
			for(int x = m_graphic->h;x > 0;++x){
				if(pixels[(y * m_graphic->h) + x] != m_graphic->format->colorkey){
					cutRect.h = y - cutRect.h;
					break;
				}
			}
			if(cutRect.h > 0)
				break;
		}

		int bpp = m_graphic->format->BitsPerPixel;

		SDL_Surface *tempSurface = SDL_CreateRGBSurface(SDL_SWSURFACE | SDL_SRCCOLORKEY | SDL_SRCALPHA | SDL_RLEACCEL,cutRect.w,cutRect.h,bpp,m_graphic->format->Rmask,m_graphic->format->Gmask,m_graphic->format->Bmask,m_graphic->format->Amask);

		if(!tempSurface)
			return false;

		SDL_Surface *newSurface = SDL_DisplayFormat(tempSurface);
		SDL_FreeSurface(tempSurface);

		if(SDL_BlitSurface(m_graphic,&cutRect,newSurface,NULL) == -1)
			return false;

		SDL_FreeSurface(m_graphic);
		m_graphic = newSurface;
	}
	return true;
}