#include "Game.h"
#include "GameObject.h"
#include "Paddle.h"
#include "Ball.h"
#include "../OpenGL/OpenGL.h"
#include "../Constants/Constants.h"
#include "..//Utils/Utils.h"
#include "../Screen Manager/ScreenManager.h"


Game::Game() :
m_AlgonquinLogo(NULL),
	m_ScoreInfoBackground(NULL),
	m_ScoreInfoGoal(NULL),
	m_ScoreInfoLeft(NULL),
	m_ScoreInfoRight(NULL),
	m_ScoreInfoNumbers(NULL),
	m_Colon(NULL),
	m_ScoreInfoTimer(0.0),
	m_ScoreInfoAlpha(0.0f),
	m_LeftGoalsScored(0),
	m_RightGoalsScored(0),
	m_Controls(true),
	m_SinglePlayer(false),
	m_Score(0),
	m_Timer(0),
	m_GameTimer(0),
	m_Win(0),
	m_ControlsTwo(false)
{
	//Create a new paddle and ball
	addGameObject(new Paddle(GAME_LEFT_PADDLE_X_PERCENTAGE));
	addGameObject(new Paddle(GAME_RIGHT_PADDLE_X_PERCENTAGE,true));
	addGameObject(new Ball());

	//Create the score info textures
	m_AlgonquinLogo = new OpenGLTexture(GAME_ALGONQUIN_LOGO);
	m_ScoreInfoBackground = new OpenGLTexture(GAME_SCORE_INFO_BACKGROUND);
	m_ScoreInfoGoal = new OpenGLTexture(GAME_SCORE_INFO_GOAL);
	m_ScoreInfoLeft = new OpenGLTexture(GAME_SCORE_INFO_LEFT);
	m_ScoreInfoRight = new OpenGLTexture(GAME_SCORE_INFO_RIGHT);

	//Create the number texture array and create the texture's in the array for each numer
	m_ScoreInfoNumbers = new OpenGLTexture *[GAME_SCORE_INFO_NUMBER_OF_NUMBERS];
	for(int i = 0; i < GAME_SCORE_INFO_NUMBER_OF_NUMBERS; i++)
	{
		m_ScoreInfoNumbers[i] = new OpenGLTexture(GAME_SCORE_INFO_NUMBERS[i]);
	}
	for(int i = 0; i < NUMBER_TEXTURES_COUNT; i++)
	{
		char buffer[2];
		sprintf(buffer, "%d",i);
		std::string atlasKey = std::string(buffer);
		m_Numbers[i] = new OpenGLTexture("Numbers",atlasKey.c_str());
	}
	m_Colon = new OpenGLTexture("Colon");
	//Reset the game
	reset();
}

Game::~Game()
{
	//Delete all the GameObject's in the vector, any GameObject add
	//to this vector will be automatically deleted here, DO NOT try
	//and delete and GameObjects yourself elsewhere.
	for(int i = 0; i < m_GameObjects.size(); i++)
	{
		delete m_GameObjects.at(i);
		m_GameObjects.at(i) = NULL;
	}

	//Clear the pointers from the vector
	m_GameObjects.clear();

	//Delete the score info background texture
	if(m_ScoreInfoBackground != NULL)
	{
		delete m_ScoreInfoBackground;
		m_ScoreInfoBackground = NULL;
	}

	//Delete the score info goal texture
	if(m_ScoreInfoGoal != NULL)
	{
		delete m_ScoreInfoGoal;
		m_ScoreInfoGoal = NULL;
	}

	//Delete the score info left texture
	if(m_ScoreInfoLeft != NULL)
	{
		delete m_ScoreInfoLeft;
		m_ScoreInfoLeft = NULL;
	}

	//Delete the score info right texture
	if(m_ScoreInfoRight != NULL)
	{
		delete m_ScoreInfoRight;
		m_ScoreInfoRight = NULL;
	}

	//Delete the score info number textures array
	if(m_ScoreInfoNumbers != NULL)
	{
		for(int i = 0; i < GAME_SCORE_INFO_NUMBER_OF_NUMBERS; i++)
		{
			delete m_ScoreInfoNumbers[i];
			m_ScoreInfoNumbers[i] = NULL;
		}

		delete[] m_ScoreInfoNumbers;
		m_ScoreInfoNumbers = NULL;
	}
	for (int i = 0; i < NUMBER_TEXTURES_COUNT; i++)
	{
		if(m_Numbers[i] != NULL)
		{
			delete m_Numbers[i];
			m_Numbers[i] = NULL;
		}
	}
	if(m_Colon != NULL)
	{
		delete m_Colon;
		m_Colon = NULL;
	}
}

void Game::update(double aDelta)
{
	//If the score timer is greater than zero, countdown
	if(m_ScoreInfoTimer > 0.0)
	{
		m_ScoreInfoTimer -= aDelta;

		//If the score timer is less than the fade out time, calculate the alpha value to fade out the score info
		if(m_ScoreInfoTimer < GAME_SCORE_INFO_FADE_OUT_TIME)
		{
			m_ScoreInfoAlpha = m_ScoreInfoTimer / GAME_SCORE_INFO_FADE_OUT_TIME;
		}

		//If the score info timer is less than zero, set it to zero
		if(m_ScoreInfoTimer < 0.0)
		{
			m_ScoreInfoTimer = 0.0;
			m_ScoreInfoAlpha = 0.0f;
		}
		return;
	}
	if(m_Timer > 0.0 && m_Timer < GAME_UNLIMITED_TIME)
	{

		if((int)m_Timer % 100 == 0)
		{
			m_Timer -= 40;
		}
		m_Timer -= aDelta;
		if(m_Timer < 0.0f)
		{
			gameOver();
		}
	}

	//Get the ball GameObject, we'll use this for collision detection
	Ball* ball = (Ball*)getGameObjectByType(GAME_BALL_TYPE);

	//Cycle through all the game objects update them and check their collision detection
	for(int i = 0; i < m_GameObjects.size(); i++)
	{
		//Make sure the GameObject is active
		if(m_GameObjects.at(i)->getIsActive() == true)
		{
			//Update the GameObject
			m_GameObjects.at(i)->update(aDelta);

			//Check collision detection against the ball
			if(m_GameObjects.at(i) != ball)
			{
				ball->checkCollision(m_GameObjects.at(i));
			}
		}
	}
}

void Game::paint()
{
	float creaseRadius = 150.0f;
	float centerIceRadius = 100.0f;

	//Draw the Goal Creases
	OpenGLRenderer::getInstance()->setLineWidth(4.0f);
	OpenGLRenderer::getInstance()->setForegroundColor(OpenGLColorRed());
	OpenGLRenderer::getInstance()->drawCircle(0.0f, getHeight() / 2.0f, creaseRadius, false);
	OpenGLRenderer::getInstance()->drawCircle(getWidth(), getHeight() / 2.0f, creaseRadius, false);

	//Draw the center red line
	OpenGLRenderer::getInstance()->setLineWidth(16.0f);
	OpenGLRenderer::getInstance()->setForegroundColor(OpenGLColorRed());
	OpenGLRenderer::getInstance()->drawLine(getWidth() / 2.0f, 0.0f, getWidth() / 2.0f, (getHeight() / 2.0f) - centerIceRadius);
	OpenGLRenderer::getInstance()->drawLine(getWidth() / 2.0f, (getHeight() / 2.0f) + centerIceRadius, getWidth() / 2.0f, getHeight());

	//Draw the blue faceoff dot and the outer blue circle
	OpenGLRenderer::getInstance()->setLineWidth(4.0f);
	OpenGLRenderer::getInstance()->setForegroundColor(OpenGLColorBlue());
	OpenGLRenderer::getInstance()->drawTexture(m_AlgonquinLogo, (getWidth() - m_AlgonquinLogo->getSourceWidth()) / 2.0f, (getHeight() - m_AlgonquinLogo->getSourceHeight()) / 2.0f);
	OpenGLRenderer::getInstance()->drawCircle(getWidth() / 2.0f, getHeight() / 2.0f, centerIceRadius, false);

	//Draw the blue line
	OpenGLRenderer::getInstance()->setForegroundColor(OpenGLColorBlue());
	OpenGLRenderer::getInstance()->setLineWidth(8.0f);
	OpenGLRenderer::getInstance()->drawLine(getWidth() * 0.25f, 0.0f, getWidth() * 0.25f, getHeight());
	OpenGLRenderer::getInstance()->drawLine(getWidth() * 0.75f, 0.0f, getWidth() * 0.75f, getHeight());

	//Draw the outer yellow walls
	OpenGLRenderer::getInstance()->setForegroundColor(OpenGLColorYellow());
	OpenGLRenderer::getInstance()->setLineWidth(8.0f);
	OpenGLRenderer::getInstance()->drawLine(0.0f, 1.0f, getWidth(), 1.0f);
	OpenGLRenderer::getInstance()->drawLine(0.0f, getHeight() - 1.0f, getWidth(), getHeight() - 1.0f);
	OpenGLRenderer::getInstance()->setLineWidth(1.0f);

	//Cycle through and draw all the game objects
	for(int i = 0; i < m_GameObjects.size(); i++)
	{
		if(m_GameObjects.at(i)->getIsActive() == true)
		{
			m_GameObjects.at(i)->paint();
		}
	}

	//Draw the score info if the alpha value is greater than zero
	if(m_ScoreInfoAlpha > 0.0f)
	{
		paintScoreInfo(m_ScoreInfoAlpha);
	}
	if(m_Timer > 0.0f)
	{
		drawNumber((int)m_Timer,getWidth() / 1.75, 10);
	}
}

void Game::reset()
{
	//Cycle through and reset all the game objects
	for(int i = 0; i < m_GameObjects.size(); i++)
	{
		m_GameObjects.at(i)->reset();
	}

	//Reset the score info timer and alpha variables
	m_ScoreInfoTimer = 0.0f;
	m_ScoreInfoAlpha = 0.0f;
	m_Timer = m_GameTimer;
	//Reset the score
	m_LeftGoalsScored = 0;
	m_RightGoalsScored = 0;
}

void Game::resetBall(bool leftGoal)
{
	//Get the ball GameObject, we need to reset it and set the current speed
	Ball* ball = (Ball*)getGameObjectByType(GAME_BALL_TYPE);
	ball->reset();

	//Which direction does the ball go in?
	leftGoal == true ? ball->setDirectionX(1.0f) : ball->setDirectionX(-1.0f);

	//Set the score info timer and alpha
	m_ScoreInfoTimer = GAME_SCORE_INFO_TIMER;
	m_ScoreInfoAlpha = 1.0f;
}

void Game::paintScoreInfo(float aAlpha)
{
	//Draw the score info background
	float backgroundX = (getWidth() - m_ScoreInfoBackground->getSourceWidth()) * 0.5f;
	float backgroundY = (getHeight() - m_ScoreInfoBackground->getSourceHeight()) * 0.5f;
	m_ScoreInfoBackground->setAlpha(aAlpha);
	OpenGLRenderer::getInstance()->drawTexture(m_ScoreInfoBackground, backgroundX, backgroundY);

	//Draw the goal title at the top
	float goalX = (getWidth() - m_ScoreInfoGoal->getSourceWidth()) * 0.5f;
	float goalY = backgroundY + (m_ScoreInfoBackground->getSourceHeight() * 0.15f) - (m_ScoreInfoLeft->getSourceHeight() / 2.0f);
	m_ScoreInfoGoal->setAlpha(aAlpha);
	OpenGLRenderer::getInstance()->drawTexture(m_ScoreInfoGoal, goalX, goalY);

	//Draw the left title
	float leftX = backgroundX + (m_ScoreInfoBackground->getSourceWidth() * 0.25f) - (m_ScoreInfoLeft->getSourceWidth() / 2.0f);
	float leftY = backgroundY + ((m_ScoreInfoBackground->getSourceHeight() - m_ScoreInfoLeft->getSourceHeight()) / 2.0f);
	m_ScoreInfoLeft->setAlpha(aAlpha);
	OpenGLRenderer::getInstance()->drawTexture(m_ScoreInfoLeft, leftX, leftY);

	//Draw the right title
	float rightX = backgroundX + (m_ScoreInfoBackground->getSourceWidth() * 0.75f) - (m_ScoreInfoRight->getSourceWidth() / 2.0f);
	float rightY = backgroundY + ((m_ScoreInfoBackground->getSourceHeight() - m_ScoreInfoRight->getSourceHeight()) / 2.0f);
	m_ScoreInfoRight->setAlpha(aAlpha);
	OpenGLRenderer::getInstance()->drawTexture(m_ScoreInfoRight, rightX, rightY);

	//Draw the left team's score
	if(m_LeftGoalsScored < GAME_SCORE_INFO_NUMBER_OF_NUMBERS)
	{
		OpenGLTexture* score = m_ScoreInfoNumbers[m_LeftGoalsScored];
		float scoreX = backgroundX + (m_ScoreInfoBackground->getSourceWidth() * 0.25f) - (score->getSourceWidth() / 2.0f);
		float scoreY = leftY + 50.0f;
		score->setAlpha(aAlpha);
		OpenGLRenderer::getInstance()->drawTexture(score, scoreX, scoreY);
	}

	//Draw the right team's score
	if(m_RightGoalsScored < GAME_SCORE_INFO_NUMBER_OF_NUMBERS)
	{
		OpenGLTexture* score = m_ScoreInfoNumbers[m_RightGoalsScored];
		float scoreX = backgroundX + (m_ScoreInfoBackground->getSourceWidth() * 0.75f) - (score->getSourceWidth() / 2.0f);
		float scoreY = rightY + 50.0f;
		score->setAlpha(aAlpha);
		OpenGLRenderer::getInstance()->drawTexture(score, scoreX, scoreY);
	}
}

void Game::gameOver()
{
	//TODO: Show the game over menu, display who
	//the winner was and what the final score was
	if(m_LeftGoalsScored > m_RightGoalsScored)
	{
		m_Win = 1;
	}
	else if(m_LeftGoalsScored < m_RightGoalsScored)
	{
		m_Win = 2;
	}
	else
	{
		m_Win = 3;
	}
	resetVariables();
	ScreenManager::getInstance()->switchScreen(GAMEOVER_SCREEN_NAME);
}

void Game::leftGoal()
{
	//Increment the left side's score
	m_LeftGoalsScored++;

	//Reset the ball
	resetBall(true);

	//If the left side has reached the goal max, end the game
	if(m_LeftGoalsScored == m_Score)
	{

		gameOver();
	}
}

void Game::rightGoal()
{
	//Increment the left side's score
	m_RightGoalsScored++;

	//Reset the ball
	resetBall(false);

	//If the right side has reached the goal max, end the game
	if(m_RightGoalsScored == m_Score)
	{

		gameOver();
	}
}

const char* Game::getName()
{
	return GAME_SCREEN_NAME;
}

void Game::screenWillAppear()
{
	OpenGLRenderer::getInstance()->setBackgroundColor(OpenGLColorWhite());
}

void Game::addGameObject(GameObject* aGameObject)
{
	if(aGameObject != NULL)
	{
		m_GameObjects.push_back(aGameObject);
	}
}

GameObject* Game::getGameObjectByType(const char* aType)
{
	//Cycle through a find the game object (if it exists)
	for(unsigned int i = 0; i < m_GameObjects.size(); i++)
	{
		if(strcmp(m_GameObjects.at(i)->getType(), aType) == 0)
		{
			return m_GameObjects.at(i);
		}
	}
	return NULL;
}

void Game::keyUpEvent(int aKeyCode)
{

	//Cycle through all the game objects update them and check their collision detection
	for(int i = 0; i < m_GameObjects.size(); i++)
	{
		//Make sure the GameObject is active
		if(m_GameObjects.at(i)->getIsActive() == true && strcmp(m_GameObjects.at(i)->getType(), GAME_PADDLE_TYPE) == 0)
		{
			Paddle* paddle = (Paddle*)m_GameObjects.at(i);
			paddle->keyUpEvent(aKeyCode);
		}
	}


}

void Game::keyDownEvent(int aKeyCode)
{
	if(aKeyCode == KEYCODE_ESCAPE)
	{
		ScreenManager::getInstance()->switchScreen(PAUSE_SCREEN_NAME);
	}

	//Cycle through all the game objects update them and check their collision detection
	for(int i = 0; i < m_GameObjects.size(); i++)
	{
		//Make sure the GameObject is active
		if(m_GameObjects.at(i)->getIsActive() == true && strcmp(m_GameObjects.at(i)->getType(), GAME_PADDLE_TYPE) == 0)
		{
			Paddle* paddle = (Paddle*)m_GameObjects.at(i);
			paddle->keyDownEvent(aKeyCode);

		}
	}

}
void Game::mouseMovementEvent(float aDeltaX, float aDeltaY, float aPositionX, float aPositionY)
{
	if(m_Controls == true)
	{
		//Set the paddle to the x position of the mouse
		Paddle* paddle = (Paddle*)getGameObjectByType(GAME_PADDLE_TYPE);

		//Safety check, paddle could be NULL
		if(paddle != NULL)
		{
			paddle->setY(aPositionY - (paddle->getHeight() / 2.0f));
		}
	}
	else if(m_ControlsTwo == true)
	{
		Paddle* paddleTwo= (Paddle*)m_GameObjects.at(1);

		if(paddleTwo != NULL)
		{
			paddleTwo->setY(aPositionY - (paddleTwo->getHeight() / 2.0f));
		}

	}
}
void Game::resetVariables()
{
	Ball* ball = (Ball*)getGameObjectByType(GAME_BALL_TYPE);
	ball->reset();
	//Reset the score info timer and alpha variables
	m_ScoreInfoTimer = 0.0f;
	m_ScoreInfoAlpha = 0.0f;
	m_Timer = m_GameTimer;
	//Reset the score
	m_LeftGoalsScored = 0;
	m_RightGoalsScored = 0;
}
void Game::setControls(bool controls)
{
	m_Controls = controls;
}
void Game::setSinglePlayer(bool players)
{
	m_SinglePlayer = players;
}
void Game::setScore(int score)
{
	m_Score = score;
}
bool Game::getSinglePlayer()
{
	return m_SinglePlayer;
}
float Game::drawNumber(int number, float x, float y)
{

	int digitToDraw = number % 10;
	OpenGLTexture* digit = m_Numbers[digitToDraw];

	float width = digit->getSourceWidth();
	x -= width;

	OpenGLRenderer::getInstance()->drawTexture(digit,x,y);


	if(number >= 10)
	{
		if(m_Timer > 59 && number < 100)
		{
			x -= m_Colon->getSourceWidth();
			OpenGLRenderer::getInstance()->drawTexture(m_Colon, x, y + 20);
		}
		width += drawNumber(number / 10, x, y);


	}
	return width;
}
void Game::setTimer(float time)
{
	m_GameTimer = time;
}
float Game::getTimer()
{
	return m_GameTimer;
}
int Game::getWin()
{
	return m_Win;
}
void Game::setControlsTwo(bool control)
{
	m_ControlsTwo = control;
}
bool Game::getControlsTwo()
{
	return m_ControlsTwo;
}
bool Game::getControls()
{
	return m_Controls;
}