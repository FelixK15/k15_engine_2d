/********************************************************************
	created:	2011/12/29
	created:	29:12:2011   23:49
	filename: 	DrawableString.h
	author:		Felix Klinge
	
	purpose:	
*********************************************************************/

#pragma once

#ifndef __DRAWABLESTRING__
#define __DRAWABLESTRING__

#include "StandardIncludes.h"
#include "GameObject.h"
#include "Color.h"

namespace K15_Engine
{
	class IFont;
	class IGraphic;

	class K15ENGINE_API DrawableString : public GameObject
	{
	public:
		DrawableString();

		DrawableString(const String& text);

		DrawableString(const DrawableString& string);
		
		~DrawableString();

		void setMaxSize(int maxSize){m_maxSize = maxSize;}

		void setMargin(int margin);

		int getLength(){return m_string.size();}

		int getMargin();

		bool setFont(const String& fontName,bool setMargin = true);

		bool setFont(FontPtr font,bool setMargin = true);

		void setColor(const Color& color);

		void setColor(U8 r,U8 g,U8 b,U8 a);

		bool update(U32 deltaTime);

		void setPosition(S16 x,S16 y);

		void setPosition(const Position& position);

		void erase(U32 start,U32 npos);

		FontPtr getFont();

		String getString(){return m_string;}

		size_t size(){return m_string.size();}

		bool empty(){return m_string.empty();}

		DrawableString &operator=(const DrawableString &drawString2);
		DrawableString &operator=(const String &string2);

		DrawableString &operator+=(const DrawableString &drawString2);
		DrawableString &operator+=(const String &string2);
		DrawableString &operator+=(const char &chr);

	private:
		void _recreateGraphics();
		void _realignGraphics();
		void _copy(const DrawableString &drawString2);

		String m_string;
		FontPtr m_font;
		Color m_color;

		int m_maxSize;
		int m_margin;
		std::list<GraphicPtr> m_objects;
	};
}

#endif //__DRAWABLESTRING__