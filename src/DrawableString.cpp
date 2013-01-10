#include "DrawableString.h"
#include "RenderableComponent.h"
#include "Log.h"
#include "IFont.h"
#include "IGraphic.h"

#include "Game.h"

using namespace K15_Engine;


DrawableString::DrawableString()
	: GameObject(), m_margin(8), m_color(Color::White)
{
	m_maxSize = 20;
	m_font = myGame->getFontManager()->createFont("font.ttf");
}

DrawableString::DrawableString( const String &text )
	: GameObject(), m_string(text), m_margin(8), m_color(Color::White)
{
	m_maxSize = 20;
	m_font = myGame->getFontManager()->createFont("font.ttf");
	_recreateGraphics();
}

DrawableString::DrawableString( const DrawableString &string2 )
	: GameObject(static_cast<GameObject>(string2)), m_string(string2.m_string), m_font(NULL)
{
	_copy(string2);
}

DrawableString::~DrawableString()
{
	
}

void DrawableString::setMargin( int margin )
{
	if(m_margin != margin){
		m_margin = margin;
		_recreateGraphics();
	}
}

int DrawableString::getMargin()
{
	return m_margin;
}

bool DrawableString::setFont( const String& fontName,bool setMargin )
{
	FontPtr newFont = myGame->getFontManager()->createFont(fontName);
	
	return setFont(newFont);
}

bool DrawableString::setFont( FontPtr font,bool setMargin )
{
	if(!font->loadedSuccessful()){
		return false;
	}else{
		if(m_font != font){
			m_font = font;
			this->setMargin(m_font->getSize());
			_recreateGraphics();
		}
	}

	return true;
}

FontPtr DrawableString::getFont()
{
	return m_font;
}

bool DrawableString::update( U32 deltaTime )
{
	if(GameObject::update(deltaTime)){
		for(std::list<GraphicPtr>::iterator i = m_objects.begin();i != m_objects.end();i++){
			myGame->getGraphicManager()->subscribeGraphic((*i));
		}

		return true;
	}

	return false;
}

void DrawableString::setColor( const Color& color )
{
	m_color = color;
}

void DrawableString::setColor( U8 r,U8 g,U8 b,U8 a )
{
	m_color = Color(r,g,b,a);
}

DrawableString & DrawableString::operator=( const DrawableString &drawString2 )
{
	m_string = drawString2.m_string;
	GameObject::operator=(static_cast<GameObject>(drawString2));

	return *this;
}

DrawableString & DrawableString::operator=( const String &string2 )
{
	m_string = string2;
	_copy(string2);

	return *this;
}

DrawableString & DrawableString::operator+=( const DrawableString &drawString2 )
{
	if(m_string.size() + drawString2.m_string.size() <= m_maxSize){
		m_string += drawString2.m_string;
		_recreateGraphics();
	}
	return *this;
}

DrawableString & DrawableString::operator+=( const String &string2 )
{
	if(m_string.size() + string2.size() <= m_maxSize){
		m_string += string2;
		_recreateGraphics();
	}	
	return *this;
}

DrawableString & DrawableString::operator+=( const char &chr )
{
	if(m_string.size() + 1 <= m_maxSize){
		m_string += chr;
		_recreateGraphics();
	}
	return *this;
}

void DrawableString::erase( U32 start,U32 npos )
{
	if(m_string.size() > 0){
		m_string = m_string.substr(0,m_string.size()-1);
		//m_string.erase(start,npos);
	}
	

	_recreateGraphics();
}

void DrawableString::setPosition( S16 x,S16 y )
{
	GameObject::setPosition(x,y);
	_realignGraphics();
}

void DrawableString::setPosition(const Position& position)
{
	GameObject::setPosition(position);
	_realignGraphics();
}

void DrawableString::_copy( const DrawableString &drawString2 )
{
	this->m_color = drawString2.m_color;
	//SAFE_DELETE(m_font);
	m_margin = drawString2.m_margin;
	m_font = drawString2.m_font;
	_recreateGraphics();
}

void DrawableString::_recreateGraphics()
{
	if(m_font->loadedSuccessful()){
		std::for_each(this->m_components.begin(),this->m_components.end(),Deleter<AbstractComponent*>);
		this->m_objects.clear();

		for(int i = 0;i != m_string.length();i++){
			char curChar = m_string.at(i);
			GraphicPtr newGraphic = myGame->getGraphicManager()->createGraphic(curChar,m_font,Position(0,0),m_color);
			m_objects.push_back(newGraphic);
		}

		_realignGraphics();
	}

}

void DrawableString::_realignGraphics()
{
	Position startPosition = this->m_position;
	for(std::list<GraphicPtr>::iterator i = m_objects.begin();i != m_objects.end();i++){
		(*i)->setPosition(startPosition);
		startPosition.setX(startPosition.getX() + m_margin);
	}

	if(m_font != NULL){
		this->m_size.setHeight(m_font->getSize());
	}else{
		this->m_size.setHeight(0);
	}

	this->m_size.setWidth(m_margin * m_objects.size());
}
