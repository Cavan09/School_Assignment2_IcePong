#include "Pause.h"
#include "../Constants/Constants.h"
#include "../Input/Input.h"
#include "../Screen Manager/ScreenManager.h"
#include "../UI/UIButton.h"
#include "../OpenGL/OpenGL.h"
#include "../Game/Game.h"
#include "../Game/Ball.h"


Pause::Pause() :
m_Background(NULL),
	m_Option(-1),
	m_Title(NULL),
	m_Return(false)
{
	addUIButton(new UIButton(PAUSE_RESUME));
	addUIButton(new UIButton(PAUSE_RESTART));
	addUIButton(new UIButton(PAUSE_GAME_SETTINGS));
	addUIButton(new UIButton(MAIN_MENU_BUTTON));
	float spaceing = MENU_SPACE_Y_PERCENTAGE;

	for( int i = 0; i < m_Buttons.size(); i++)
	{
		m_Buttons[i]->setCenterPosition(getWidth() / 2.0f, getHeight() * (MAINMENU_SINGLE_PLAYER_Y_PERCENTAGE + spaceing));
		m_Buttons[i]->setListener(this);
		spaceing += MENU_SPACE_Y_PERCENTAGE;
	}

	m_Background = new OpenGLTexture(MENU_BACKGROUND);
	m_Title = new OpenGLTexture(PAUSE_TITLE);
}


Pause::~Pause()
{
	for(int i = 0; i < m_Buttons.size(); i++)
	{
		delete m_Buttons.at(i);
		m_Buttons.at(i) = NULL;
	}
	if(m_Background != NULL)
	{
		delete m_Background;
		m_Background = NULL;
	}
	if(m_Title != NULL)
	{
		delete m_Title;
		m_Title = NULL;
	}
}

const char* Pause::getName()
{
	return PAUSE_SCREEN_NAME;

}

void Pause::update(double delta)
{

}

void Pause::paint()
{	
	OpenGLRenderer::getInstance()->drawTexture(m_Background,0.0f,0.0f);
	OpenGLRenderer::getInstance()->drawTexture(m_Title,TITLE_X_POSITION - m_Title->getSourceWidth() / 2,TITLE_Y_POSITION - m_Title->getSourceHeight());
	for(int i = 0; i < m_Buttons.size(); i++)
	{
		m_Buttons[i]->paint();
	}
}
void Pause::keyUpEvent(int keyCode)
{
	Game* game = (Game*)ScreenManager::getInstance()->getScreenForName(GAME_SCREEN_NAME);
	if(keyCode == KEYCODE_RETURN)
	{
		if(m_Buttons[0]->getIsSelected() == true)
		{
			ScreenManager::getInstance()->switchScreen(GAME_SCREEN_NAME);
		}
		if(m_Buttons[1]->getIsSelected() == true)
		{

			game->resetVariables();
			ScreenManager::getInstance()->switchScreen(GAME_SCREEN_NAME);
		}
		if(m_Buttons[2]->getIsSelected() == true)
		{
			if(game->getSinglePlayer() == true)
			{
				m_Return = true;
				ScreenManager::getInstance()->switchScreen(SINGLESETTINGS_SCREEN_NAME);
			}
			else
			{
				m_Return = true;
				ScreenManager::getInstance()->switchScreen(MULTISETTINGS_SCREEN_NAME);
			}

		}
		if(m_Buttons[3]->getIsSelected() == true)
		{
			m_Return = false;
			ScreenManager::getInstance()->switchScreen(MAINMENU_SCREEN_NAME);
		}
	}
	if(keyCode ==  KEYCODE_DOWN_ARROW)
	{


		m_Option++;
		if( m_Option >= m_Buttons.size())
		{
			m_Option = 0;
		}

		for (int i= 0; i < m_Buttons.size(); i++)
		{
			if(i == m_Option)
			{
				m_Buttons[i]->setIsSelected(true);
			}
			else if(i != m_Option)
			{
				m_Buttons[i]->setIsSelected(false);
			}
		}
	}
	if(keyCode ==  KEYCODE_UP_ARROW)
	{

		m_Option --;
		if( m_Option < 0)
		{
			m_Option = 3;
		}
		for (int i= 0; i < m_Buttons.size(); i++)
		{
			if(i == m_Option)
			{
				m_Buttons[i]->setIsSelected(true);
			}
			else if(i != m_Option)
			{
				m_Buttons[i]->setIsSelected(false);
			}

		}

	}
}

void Pause::mouseMovementEvent(float deltaX, float deltaY, float positionX, float positionY)
{
	for(int i = 0; i < m_Buttons.size(); i++)
	{
		m_Buttons[i]->mouseMovementEvent(positionX,positionY);
	}
}
void Pause::mouseLeftClickUpEvent(float positionX, float positionY)
{
	for(int i = 0; i < m_Buttons.size(); i++)
	{
		m_Buttons[i]->mouseLeftClickUpEvent(positionX,positionY);
	}
}
void Pause::buttonAction(UIButton* button)
{
	Game* game = (Game*)ScreenManager::getInstance()->getScreenForName(GAME_SCREEN_NAME);
	if(button == m_Buttons[0])
	{
		ScreenManager::getInstance()->switchScreen(GAME_SCREEN_NAME);
	}
	if(button == m_Buttons[1])
	{
		game->resetVariables();
		ScreenManager::getInstance()->switchScreen(GAME_SCREEN_NAME);

	}
	if(button == m_Buttons[2])
	{
		if(game->getSinglePlayer() == true)
		{
			m_Return = true;
			ScreenManager::getInstance()->switchScreen(SINGLESETTINGS_SCREEN_NAME);
		}
		else
		{
			m_Return = true;
			ScreenManager::getInstance()->switchScreen(MULTISETTINGS_SCREEN_NAME);
		}
	}
	if(button == m_Buttons[3])
	{
		m_Return = false;
		ScreenManager::getInstance()->switchScreen(MAINMENU_SCREEN_NAME);
	}

}
void Pause::addUIButton(UIButton* aUIButton)
{
	if(aUIButton != NULL)
	{
		m_Buttons.push_back(aUIButton);
	}
}
bool Pause::getReturn()
{
	return m_Return;
}