#pragma once

#ifndef __VARIANT__
#define __VARIANT__

#include "StandardIncludes.h"

namespace K15_Engine
{
	enum Variant_Type{
		TYPE_INTEGER,
		TYPE_FLOAT,
		TYPE_DOUBLE,
		TYPE_BOOL,
		TYPE_STRING,
		TYPE_USERDATA,
		TYPE_GRAPHIC,
		TYPE_FONT,
		TYPE_MUSIC,
		TYPE_SOUND,
		TYPE_EMPTY
	};

	class K15ENGINE_API Variant
	{
	public:

		Variant()
		{
			type = TYPE_EMPTY;
		}

		Variant(const Variant &var)
		{
			type = var.type;
			if(type == TYPE_INTEGER){
				toInteger = var.toInteger;
			}else if(type == TYPE_FLOAT){
				toFloat = var.toFloat;
			}else if(type == TYPE_BOOL){
				toBool = var.toBool;
			}else if(type == TYPE_STRING){
				toString = var.toString;
			}else if(type == TYPE_USERDATA){
				toUserData = var.toUserData;
			}else if(type == TYPE_GRAPHIC){
				toGraphic = var.toGraphic;
			}else if(type == TYPE_FONT){
				toFont = var.toFont;
			}else if(type == TYPE_MUSIC){
				toMusic = var.toMusic;
			}else if(type == TYPE_SOUND){
				toSound = var.toSound;
			}
		}

		Variant(int integer)
		{
			type = TYPE_INTEGER;
			toInteger = integer;
		}

		Variant(float real)
		{
			type = TYPE_FLOAT;
			toFloat = real;
		}

		Variant(double dbl)
		{
			type = TYPE_DOUBLE;
			toDouble = dbl;
		}

		Variant(bool b)
		{
			type = TYPE_BOOL;
			toBool = b;
		}

		Variant(const String& string)
		{
			toString = new char[string.size() + 1];
			strcpy_s(toString,string.size() + 1,string.c_str());
			type = TYPE_STRING;
		}

// 		Variant(void *userData)
// 			:toUserData(userData)
// 		{
// 			type = TYPE_USERDATA;
// 		}

		Variant(GraphicPtr graphic)
			: toGraphic(graphic)
		{
			type = TYPE_GRAPHIC;
		}

		Variant(FontPtr font)
			: toFont(font)
		{
			type = TYPE_FONT;
		}

		Variant(MusicPtr music)
			: toMusic(music)
		{
			type = TYPE_MUSIC;
		}

		Variant(SoundPtr sound)
			: toSound(sound)
		{
			type = TYPE_SOUND;
		}

		~Variant()
		{  };

		Variant_Type type;

		union
		{
			F32 toFloat;
			double toDouble;
			int toInteger;
			bool toBool;
			char* toString;
			void *toUserData;
		};

		GraphicPtr toGraphic;
		FontPtr toFont;
		MusicPtr toMusic;
		SoundPtr toSound;
	};
}

#endif //__VARIANT__