#include "AbstractWindow.h"

using namespace K15_Engine;

AbstractWindow::~AbstractWindow()
{

}

bool AbstractWindow::isActive()
{
	return m_active;
}

bool AbstractWindow::isFullScreen()
{
	return m_fullscreen;
}

const String& AbstractWindow::getCaption()
{
	return m_caption;
}

void AbstractWindow::setFullScreen( bool fullscreen )
{
	if(fullscreen != m_fullscreen){
		reCreate();
	}
}
