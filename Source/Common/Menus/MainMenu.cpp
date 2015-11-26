#include "MainMenu.h"
#include "../Constants/Constants.h"
#include "../Input/Input.h"
#include "../Screen Manager/ScreenManager.h"
#include "../UI/UIButton.h"
#include "../OpenGL/OpenGL.h"
#include "../Game/Game.h"


MainMenu::MainMenu() :
m_Background(NULL),
	m_Option(-1),
	m_Multiplayer(false),
	m_Title(NULL)

{
	addUIButton(new UIButton(MAINMENU_SINGLE_PLAYER));
	addUIButton(new UIButton(MAINMENU_MULTI_PLAYER));
	addUIButton(new UIButton(MAINMENU_CREDITS));
	addUIButton(new UIButton(MAINMENU_EXIT));
	float spaceing = MENU_SPACE_Y_PERCENTAGE;
	for (int i = 0; i< m_Buttons.size(); i++)
	{

		m_Buttons[i]->setCenterPosition(getWidth() / 2.0f, getHeight() * (MAINMENU_SINGLE_PLAYER_Y_PERCENTAGE + spaceing));
		m_Buttons[i]->setListener(this);
		spaceing += MENU_SPACE_Y_PERCENTAGE;
	}

	m_Background = new OpenGLTexture(MENU_BACKGROUND);
	m_Title = new OpenGLTexture(MAINMENU_TITLE);
}


MainMenu::~MainMenu()
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

const char* MainMenu::getName()
{
	return MAINMENU_SCREEN_NAME;

}

void MainMenu::update(double delta)
{

}

void MainMenu::paint()
{
	OpenGLRenderer::getInstance()->drawTexture(m_Background,0.0f,0.0f);
	OpenGLRenderer::getInstance()->drawTexture(m_Title,TITLE_X_POSITION - m_Title->getSourceWidth() / 2,TITLE_Y_POSITION - m_Title->getSourceHeight());
	for(int i = 0; i< m_Buttons.size(); i++)
	{
		m_Buttons[i]->paint();
	}
}
void MainMenu::keyUpEvent(int keyCode)
{
	if(keyCode == KEYCODE_RETURN)
	{
		for (int i = 0; i < m_Buttons.size(); i++)
		{
			if (m_Buttons[0]->getIsSelected() == true)
			{
				m_Multiplayer = false;
				ScreenManager::getInstance()->switchScreen(SINGLESETTINGS_SCREEN_NAME);
			}
			if (m_Buttons[1]->getIsSelected() == true)
			{
				m_Multiplayer = true;
				ScreenManager::getInstance()->switchScreen(MULTISETTINGS_SCREEN_NAME);
			}
			if (m_Buttons[2]->getIsSelected() == true)
			{
				ScreenManager::getInstance()->switchScreen(CREDITS_SCREEN_NAME);
			}
			if (m_Buttons[3]->getIsSelected() == true)
			{
				exit(0);
			}
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

void MainMenu::mouseMovementEvent(float deltaX, float deltaY, float positionX, float positionY)
{
	for(int i = 0; i < m_Buttons.size(); i++)
	{
		m_Buttons[i]->mouseMovementEvent(positionX,positionY);
	}
}
void MainMenu::mouseLeftClickUpEvent(float positionX, float positionY)
{
	for(int i = 0; i < m_Buttons.size(); i++)
	{
		m_Buttons[i]->mouseLeftClickUpEvent(positionX,positionY);
	}
}
void MainMenu::buttonAction(UIButton* button)
{
	if(button == m_Buttons[0])
	{
		m_Multiplayer = false;
		ScreenManager::getInstance()->switchScreen(SINGLESETTINGS_SCREEN_NAME);
	}
	if(button == m_Buttons[1])
	{
		m_Multiplayer = true;
		ScreenManager::getInstance()->switchScreen(MULTISETTINGS_SCREEN_NAME);
	}
	if(button == m_Buttons[2])
	{
		ScreenManager::getInstance()->switchScreen(CREDITS_SCREEN_NAME);
	}
	if(button == m_Buttons[3])
	{
		exit(0);
	}

}
void MainMenu::addUIButton(UIButton* aUIButton)
{
	if(aUIButton != NULL)
	{
		m_Buttons.push_back(aUIButton);
	}
}
bool MainMenu::getMultiplayer()
{
	return m_Multiplayer;
}