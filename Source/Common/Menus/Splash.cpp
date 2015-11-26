#include "Splash.h"
#include "../Constants/Constants.h"
#include "../Input/Input.h"
#include "../Screen Manager/ScreenManager.h"
#include "../UI/UIButton.h"
#include "../OpenGL/OpenGL.h"


Splash::Splash() :
m_PressSpace(NULL),
	m_Background(NULL),
	m_Title(NULL)
{
	m_PressSpace = new UIButton(SPLASH_PRESS_SPACE);
	m_PressSpace->setCenterPosition(getWidth() / 2.0f, getHeight() * SPLASH_PRESS_SPACE_Y_PERCENTAGE);
	m_PressSpace->setListener(this);
	m_Background = new OpenGLTexture(MENU_BACKGROUND);
	m_Title = new OpenGLTexture(SPLASH_TITLE);
}


Splash::~Splash()
{
	if(m_PressSpace != NULL)
	{
		delete m_PressSpace;
		m_PressSpace = NULL;

	}
	if(m_Background != NULL)
	{
		delete m_Background;
		m_Background = NULL;
	}
}

const char* Splash::getName()
{
	return SPLASH_SCREEN_NAME;

}

void Splash::update(double delta)
{

}

void Splash::paint()
{	
	OpenGLRenderer::getInstance()->drawTexture(m_Background,0.0f,0.0f);
	OpenGLRenderer::getInstance()->drawTexture(m_Title,TITLE_X_POSITION - m_Title->getSourceWidth() / 2,TITLE_Y_POSITION - m_Title->getSourceHeight()+200);
	m_PressSpace->paint();
}
void Splash::keyUpEvent(int keyCode)
{
	if(keyCode == KEYCODE_SPACE)
	{
		ScreenManager::getInstance()->switchScreen(MAINMENU_SCREEN_NAME);
	}
}

void Splash::mouseMovementEvent(float deltaX, float deltaY, float positionX, float positionY)
{
	m_PressSpace->mouseMovementEvent(positionX,positionY);
}
void Splash::mouseLeftClickUpEvent(float positionX, float positionY)
{
	m_PressSpace->mouseLeftClickUpEvent(positionX,positionY);
}
void Splash::buttonAction(UIButton* button)
{
	if(button == m_PressSpace)
	{
		ScreenManager::getInstance()->switchScreen(MAINMENU_SCREEN_NAME);

	}

}