#include "GameOver.h"
#include "../Constants/Constants.h"
#include "../Input/Input.h"
#include "../Screen Manager/ScreenManager.h"
#include "../UI/UIButton.h"
#include "../OpenGL/OpenGL.h"
#include "../Game/Game.h"


GameOver::GameOver() :

m_Background(NULL),
	m_Option(-1),
	m_Title(NULL),
	m_WinOne(NULL),
	m_WinTwo(NULL),
	m_Tie(NULL)
{
	addUIButton(new UIButton(MAIN_MENU_BUTTON));
	addUIButton(new UIButton(PLAY_AGAIN_BUTTON));
	float spaceing = MENU_SPACE_Y_PERCENTAGE;

	for( int i = 0; i < m_Buttons.size(); i++)
	{
		m_Buttons[i]->setCenterPosition(getWidth() / 2.0f, getHeight() * (MAINMENU_SINGLE_PLAYER_Y_PERCENTAGE + spaceing));
		m_Buttons[i]->setListener(this);
		spaceing += MENU_SPACE_Y_PERCENTAGE;
	}
	m_Background = new OpenGLTexture(MENU_BACKGROUND);
	m_Title = new OpenGLTexture(GAMEOVER_TITLE);
	m_WinOne = new OpenGLTexture(WIN_ONE);
	m_WinTwo = new OpenGLTexture(WIN_TWO);
	m_Tie = new OpenGLTexture(TIE);
}


GameOver::~GameOver()
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
	if(m_WinOne != NULL)
	{
		delete m_WinOne;
		m_WinOne = NULL;
	}
	if(m_WinTwo != NULL)
	{
		delete m_WinTwo;
		m_WinTwo = NULL;
	}
	if(m_Tie != NULL)
	{
		delete m_Tie;
		m_Tie = NULL;
	}
}

const char* GameOver::getName()
{
	return GAMEOVER_SCREEN_NAME;

}

void GameOver::update(double delta)
{

}

void GameOver::paint()
{	
	Game* game = (Game*)ScreenManager::getInstance()->getScreenForName(GAME_SCREEN_NAME);
	OpenGLRenderer::getInstance()->drawTexture(m_Background,0.0f,0.0f);
	if(game->getWin() == 1)
	{
		OpenGLRenderer::getInstance()->drawTexture(m_WinOne,m_WinOne->getSourceWidth() / 2.0f + 300.0f,m_WinOne->getSourceWidth() / 2.0f + 180.0f);
	}
	else if(game->getWin() == 2)
	{
		OpenGLRenderer::getInstance()->drawTexture(m_WinTwo,m_WinTwo->getSourceWidth() / 2.0f + 300.0f,m_WinTwo->getSourceWidth() / 2.0f + 180.0f);
	}
	else
	{
		OpenGLRenderer::getInstance()->drawTexture(m_Tie,m_Tie->getSourceWidth() / 2.0f + 300.0f,m_Tie->getSourceWidth() / 2.0f + 180.0f);
	}
	OpenGLRenderer::getInstance()->drawTexture(m_Title,TITLE_X_POSITION - m_Title->getSourceWidth() / 2,TITLE_Y_POSITION - m_Title->getSourceHeight());
	for(int i = 0; i < m_Buttons.size(); i++)
	{
		m_Buttons[i]->paint();
	}
}
void GameOver::keyUpEvent(int keyCode)
{

	if(keyCode == KEYCODE_RETURN)
	{
		if(m_Buttons[0]->getIsSelected() == true)
		{
			ScreenManager::getInstance()->switchScreen(MAINMENU_SCREEN_NAME);
		}
		if(m_Buttons[1]->getIsSelected() == true)
		{
			ScreenManager::getInstance()->switchScreen(GAME_SCREEN_NAME);
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
			m_Option = 1;
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

void GameOver::mouseMovementEvent(float deltaX, float deltaY, float positionX, float positionY)
{
	for(int i = 0; i < m_Buttons.size(); i++)
	{
		m_Buttons[i]->mouseMovementEvent(positionX,positionY);
	}
}
void GameOver::mouseLeftClickUpEvent(float positionX, float positionY)
{
	for(int i = 0; i < m_Buttons.size(); i++)
	{
		m_Buttons[i]->mouseLeftClickUpEvent(positionX,positionY);
	}
}
void GameOver::buttonAction(UIButton* button)
{
	if(button == m_Buttons[0])
	{
		ScreenManager::getInstance()->switchScreen(MAINMENU_SCREEN_NAME);

	}
	if(button == m_Buttons[1])
	{
		ScreenManager::getInstance()->switchScreen(GAME_SCREEN_NAME);
	}
}
void GameOver::addUIButton(UIButton* aUIButton)
{
	if(aUIButton != NULL)
	{
		m_Buttons.push_back(aUIButton);
	}
}