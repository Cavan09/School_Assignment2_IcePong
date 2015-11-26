#include "Credits.h"
#include "../Constants/Constants.h"
#include "../Input/Input.h"
#include "../Screen Manager/ScreenManager.h"
#include "../UI/UIButton.h"
#include "../OpenGL/OpenGL.h"


Credits::Credits() :
m_Back(NULL),
	m_Background(NULL),
	m_Text(NULL)
{
	m_Back = new UIButton(BACK_BUTTON);
	m_Back->setCenterPosition(getWidth() / 2.0f, getHeight() * BACK_BUTTON_Y_PERCENTAGE);
	m_Back->setListener(this);
	m_Text = new OpenGLTexture(CREDITS_TEXT);
	m_Background = new OpenGLTexture(MENU_BACKGROUND);
}


Credits::~Credits()
{
	if(m_Back != NULL)
	{
		delete m_Back;
		m_Back = NULL;

	}
	if(m_Background != NULL)
	{
		delete m_Background;
		m_Background = NULL;
	}
}

const char* Credits::getName()
{
	return CREDITS_SCREEN_NAME;

}

void Credits::update(double delta)
{

}

void Credits::paint()
{	
	OpenGLRenderer::getInstance()->drawTexture(m_Background,0.0f,0.0f);
	OpenGLRenderer::getInstance()->drawTexture(m_Text,200.0f,100.0f);
	m_Back->paint();
}
void Credits::keyUpEvent(int keyCode)
{
	if(keyCode == KEYCODE_DOWN_ARROW)
	{
		if(m_Back->getIsSelected() == false)
		{
			m_Back->setIsSelected(true);
		}
		else
		{
			m_Back->setIsSelected(false);
		}
	}
	if(keyCode == KEYCODE_UP_ARROW)
	{
		if(m_Back->getIsSelected() == false)
		{
			m_Back->setIsSelected(true);
		}
		else
		{
			m_Back->setIsSelected(false);
		}
	}
	if(keyCode == KEYCODE_RETURN)
	{
		if(m_Back->getIsSelected() == true)
		{
			ScreenManager::getInstance()->switchScreen(MAINMENU_SCREEN_NAME);
		}
	}
}

void Credits::mouseMovementEvent(float deltaX, float deltaY, float positionX, float positionY)
{
	m_Back->mouseMovementEvent(positionX,positionY);
}
void Credits::mouseLeftClickUpEvent(float positionX, float positionY)
{
	m_Back->mouseLeftClickUpEvent(positionX,positionY);
}
void Credits::buttonAction(UIButton* button)
{
	if(button == m_Back)
	{
		ScreenManager::getInstance()->switchScreen(MAINMENU_SCREEN_NAME);

	}

}