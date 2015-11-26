#include "MultiSettings.h"
#include "../Constants/Constants.h"
#include "../Input/Input.h"
#include "../Screen Manager/ScreenManager.h"
#include "../UI/UIButton.h"
#include "../OpenGL/OpenGL.h"
#include "../Game/Game.h"
#include "../Game/Paddle.h"
#include "Pause.h"


MultiSettings::MultiSettings() :
m_Background(NULL),
	m_Option(-1),
	m_SelectScore(1),
	m_SelectTime(1),
	m_SelectAi(1),
	m_SelectInput(1),
	m_Title(NULL)
{
	addUIButton(new UIButton(SCORE_SETTING));
	addUIButton(new UIButton(TIME_SETTING));
	addUIButton(new UIButton(CONTROLS_SETTING));
	addUIButton(new UIButton(CONTROLS_SETTING));
	addUIButton(new UIButton(START_GAME));
	addUIButton(new UIButton(BACK_BUTTON));
	addSubUIButton(new SubUIButton(SETTING_SCORE));
	addSubUIButton(new SubUIButton(SETTING_TIME));
	addSubUIButton(new SubUIButton(SETTING_INPUT));
	addSubUIButton(new SubUIButton(SETTING_INPUT));

	float spaceing = MENU_SPACE_Y_PERCENTAGE;
	for (int i = 0; i < m_Buttons.size(); i++)
	{

		if( i <= 3)
		{
			m_Buttons[i]->setRightPosition(getWidth() / 2.0f, getHeight() * (SINGLESETTINGS_SCORE_Y_PERCENTAGE + spaceing));
			m_Buttons[i]->setListener(this);
			spaceing += MENU_SPACE_Y_PERCENTAGE /1.2f;
		}
		else if( i >= 4)
		{
			m_Buttons[i]->setCenterPosition(getWidth() / 2.0f, getHeight() * (SINGLESETTINGS_SCORE_Y_PERCENTAGE + spaceing));
			m_Buttons[i]->setListener(this);
			spaceing += MENU_SPACE_Y_PERCENTAGE /1.2f;
		}

	}

	spaceing = MENU_SPACE_Y_PERCENTAGE;
	for (int i = 0; i < m_Settings.size(); i++)
	{
		m_Settings[i]->setPosition(getWidth() / 1.7f, getHeight() * (SINGLESETTINGS_SCORE_Y_PERCENTAGE + spaceing));
		spaceing += MENU_SPACE_Y_PERCENTAGE /1.2f;
	}

	m_Background = new OpenGLTexture(MENU_BACKGROUND);
	m_Title = new OpenGLTexture(MULTI_TITLE);
}


MultiSettings::~MultiSettings()
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

const char* MultiSettings::getName()
{
	return MULTISETTINGS_SCREEN_NAME;

}

void MultiSettings::update(double delta)
{

}

void MultiSettings::paint()
{	
	OpenGLRenderer::getInstance()->drawTexture(m_Background,0.0f,0.0f);
	OpenGLRenderer::getInstance()->drawTexture(m_Title,TITLE_X_POSITION - m_Title->getSourceWidth() / 2,TITLE_Y_POSITION - m_Title->getSourceHeight() + 50);
	for(int i = 0; i< m_Buttons.size(); i++)
	{
		m_Buttons[i]->paint();
	}
	for(int i = 0; i < m_Settings.size(); i++)
	{
		m_Settings[i]->paint();
	}
}
void MultiSettings::keyUpEvent(int keyCode)
{
	if(keyCode == KEYCODE_RETURN)
	{
		Game* game = (Game*)ScreenManager::getInstance()->getScreenForName(GAME_SCREEN_NAME);

		if(m_Buttons[0]->getIsSelected() == true)
		{
			m_SelectScore++;
			m_Settings[0]->setSelected(m_SelectScore);
			if(m_SelectScore > 4)
			{
				m_SelectScore = 1;
			}
		}
		if(m_Buttons[1]->getIsSelected() == true)
		{
			m_SelectTime++;
			m_Settings[1]->setSelected(m_SelectTime);
			if(m_SelectTime > 4)
			{
				m_SelectTime = 1;
			}
		}
		if(m_Buttons[2]->getIsSelected() == true)
		{
			if(m_SelectInput == 1)
			{
				m_SelectAi++;
				m_Settings[2]->setSelected(m_SelectAi);
				if(m_SelectAi >= 2)
				{
					m_SelectAi = 0;
				}
			}
		}
		if(m_Buttons[3]->getIsSelected() == true)
		{
			if(m_SelectAi == 1)
			{
				m_SelectInput++;
				m_Settings[3]->setSelected(m_SelectInput);
				if(m_SelectInput >= 2)
				{
					m_SelectInput = 0;
				}
			}
		}
		if(m_Buttons[4]->getIsSelected() == true)
		{

			if(m_SelectScore == 1)
			{
				game->setScore(GAME_SCORE_THREE);
			}
			else if(m_SelectScore == 2)
			{
				game->setScore(GAME_SCORE_SIX);
			}
			else if(m_SelectScore == 3)
			{
				game->setScore(GAME_SCORE_NINE);
			}
			else if(m_SelectScore == 4)
			{
				game->setScore(GAME_SCORE_UNLIMITED);
			}
			if(m_SelectTime == 1)
			{
				game->setTimer(GAME_THREE_MINUTES);
			}
			else if(m_SelectTime == 2)
			{
				game->setTimer(GAME_SIX_MINUTES);
			}
			else if(m_SelectTime == 3)
			{
				game->setTimer(GAME_NINE_MINUTES);
			}
			else if(m_SelectTime == 4)
			{
				game->setTimer(GAME_THREE_MINUTES);
			}
			if(m_SelectAi == 1)
			{
				game->setControls(false);
			}
			else if(m_SelectAi == 0)
			{
				game->setControls(true);
			}
			if(m_SelectInput == 1)
			{
				game->setControlsTwo(false);
			}
			else if(m_SelectInput == 0)
			{
				game->setControlsTwo(true);
			}

			game->reset();
			game->setSinglePlayer(false);
			ScreenManager::getInstance()->switchScreen(GAME_SCREEN_NAME);
		}
		if(m_Buttons[5]->getIsSelected() == true)
		{
			Pause* pause = (Pause*)ScreenManager::getInstance()->getScreenForName(PAUSE_SCREEN_NAME);
			if(pause->getReturn() == false)
			{
				ScreenManager::getInstance()->switchScreen(MAINMENU_SCREEN_NAME);
			}
			else
			{
				ScreenManager::getInstance()->switchScreen(PAUSE_SCREEN_NAME);
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
			m_Option = 5;
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

void MultiSettings::mouseMovementEvent(float deltaX, float deltaY, float positionX, float positionY)
{
	for(int i = 0; i < m_Buttons.size(); i++)
	{
		m_Buttons[i]->mouseMovementEvent(positionX,positionY);
	}
}
void MultiSettings::mouseLeftClickUpEvent(float positionX, float positionY)
{
	for(int i = 0; i < m_Buttons.size(); i++)
	{
		m_Buttons[i]->mouseLeftClickUpEvent(positionX,positionY);
	}
}
void MultiSettings::buttonAction(UIButton* button)
{
	if(button == m_Buttons[0])
	{
		m_SelectScore++;
		m_Settings[0]->setSelected(m_SelectScore);
		if(m_SelectScore > 4)
		{
			m_SelectScore = 1;
		}
	}
	if(button == m_Buttons[1])
	{
		m_SelectTime++;
		m_Settings[1]->setSelected(m_SelectTime);
		if(m_SelectTime > 4)
		{
			m_SelectTime = 1;
		}
	}
	if(button == m_Buttons[2])
	{
		if(m_SelectInput ==1)
		{
			m_SelectAi++;
			m_Settings[2]->setSelected(m_SelectAi);
			if(m_SelectAi >= 2)
			{
				m_SelectAi = 0;
			}
		}
	}
	if(button == m_Buttons[3])
	{

		if(m_SelectAi == 1)
		{
			m_SelectInput++;
			m_Settings[3]->setSelected(m_SelectInput);
			if(m_SelectInput >= 2)
			{
				m_SelectInput = 0;
			}
		}
	}
	if(button == m_Buttons[4])
	{
		Game* game = (Game*)ScreenManager::getInstance()->getScreenForName(GAME_SCREEN_NAME);
		if(m_SelectScore == 1)
		{
			game->setScore(GAME_SCORE_THREE);
		}
		else if(m_SelectScore == 2)
		{
			game->setScore(GAME_SCORE_SIX);
		}
		else if(m_SelectScore == 3)
		{
			game->setScore(GAME_SCORE_NINE);
		}
		else if(m_SelectScore == 4)
		{
			game->setScore(GAME_SCORE_UNLIMITED);
		}
		if(m_SelectTime == 1)
		{
			game->setTimer(GAME_THREE_MINUTES);
		}
		else if(m_SelectTime == 2)
		{
			game->setTimer(GAME_SIX_MINUTES);
		}
		else if(m_SelectTime == 3)
		{
			game->setTimer(GAME_NINE_MINUTES);
		}
		else if(m_SelectTime == 4)
		{
			game->setTimer(GAME_THREE_MINUTES);
		}
		if(m_SelectAi == 1)
		{
			game->setControls(false);
		}
		else if(m_SelectAi == 0)
		{
			game->setControls(true);
		}
		if(m_SelectInput == 1)
		{
			game->setControlsTwo(false);
		}
		else if(m_SelectInput == 0)
		{
			game->setControlsTwo(true);
		}

		game->reset();
		game->setSinglePlayer(false);
		ScreenManager::getInstance()->switchScreen(GAME_SCREEN_NAME);

	}
	if(button == m_Buttons[5])
	{
		Pause* pause = (Pause*)ScreenManager::getInstance()->getScreenForName(PAUSE_SCREEN_NAME);
		if(pause->getReturn() == false)
		{
			ScreenManager::getInstance()->switchScreen(MAINMENU_SCREEN_NAME);
		}
		else
		{
			ScreenManager::getInstance()->switchScreen(PAUSE_SCREEN_NAME);
		}
	}

}
void MultiSettings::addUIButton(UIButton* aUIButton)
{
	if(aUIButton != NULL)
	{
		m_Buttons.push_back(aUIButton);
	}
}
void MultiSettings::addSubUIButton(SubUIButton* aSubUIButton)
{
	if(aSubUIButton != NULL)
	{
		m_Settings.push_back(aSubUIButton);
	}
}