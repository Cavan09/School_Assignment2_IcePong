//
//  Paddle.cpp
//  GAM-1532 OSX Game
//
//  Created by Bradley Flood on 2013-01-09.
//  Copyright (c) 2013 Algonquin College. All rights reserved.
//

#include "Paddle.h"
#include "Ball.h"
#include "Game.h"
#include "../Constants/Constants.h"
#include "../Screen Manager/ScreenManager.h"
#include "../OpenGL/OpenGL.h"
#include "../Utils/Utils.h"
#include "../Input/Input.h"
#include "../Menus/MainMenu.h"



Paddle::Paddle(float aOffsetX, bool aComputerController) : GameObject(),
	m_Width(0.0f),
	m_Height(0.0f),
	m_OffsetPercentageX(0.0f),
	m_Speed(0.0f),
	m_ComputerControlled(false),
	m_UpArrowPressed(false),
	m_DownArrowPressed(false),
	m_WPressed(false),
	m_SPressed(false),
	m_Player(false)
{
	m_OffsetPercentageX = aOffsetX;
	m_ComputerControlled = aComputerController;
}

Paddle::~Paddle()
{

}

void Paddle::update(double aDelta)
{
	Game* game = (Game*)ScreenManager::getInstance()->getScreenForName(GAME_SCREEN_NAME);
	MainMenu* menu = (MainMenu*)ScreenManager::getInstance()->getScreenForName(MAINMENU_SCREEN_NAME);
	m_Player = menu->getMultiplayer();
	//User controlled input
	if(m_ComputerControlled == false && game->getControls() == false)
	{
		if(m_UpArrowPressed == true && m_DownArrowPressed == false)
		{
			m_Speed += -GAME_PADDLE_ACCELERATION;
			m_Speed = MIN_VALUE(m_Speed, -GAME_PADDLE_MAX_SPEED);
		}
		else if(m_UpArrowPressed == false && m_DownArrowPressed == true)
		{
			m_Speed += GAME_PADDLE_ACCELERATION;
			m_Speed = MAX_VALUE(m_Speed, GAME_PADDLE_MAX_SPEED);
		}
		else if(m_UpArrowPressed == true && m_DownArrowPressed == true)
		{
			m_Speed = 0.0f;
		}
		else
		{
			m_Speed = 0.0f;
		}
	}
	//Computer controller input
	else if(m_ComputerControlled == true && m_Player == true && game->getControlsTwo() == false)
	{
		if(m_WPressed == true && m_SPressed == false)
		{
			m_Speed += -GAME_PADDLE_ACCELERATION;
			m_Speed = MIN_VALUE(m_Speed, -GAME_PADDLE_MAX_SPEED);
		}
		else if(m_WPressed == false && m_SPressed == true)
		{
			m_Speed += GAME_PADDLE_ACCELERATION;
			m_Speed = MAX_VALUE(m_Speed, GAME_PADDLE_MAX_SPEED);
		}
		else if(m_WPressed == true && m_SPressed == true)
		{
			m_Speed = 0.0f;
		}
		else
		{
			m_Speed = 0.0f;
		}
	}

	else if (m_ComputerControlled == true && m_Player == false)
	{
		//Get a pointer to the game from the screen manager, so that we can use it to get a pointer to the game.
		Game* game = (Game*)ScreenManager::getInstance()->getScreenForName(GAME_SCREEN_NAME);
		Ball* ball = (Ball*)game->getGameObjectByType(GAME_BALL_TYPE);

		//Get the ball's y value and the center of the paddle's y value
		float ballY = ball->getY();
		float paddleCenterY = getY() + (getHeight() / 2.0f);

		//Set the speed based on the paddle's y distance from the ball's
		if(ballY < paddleCenterY)
		{
			m_Speed += -GAME_PADDLE_ACCELERATION;
			m_Speed = MIN_VALUE(m_Speed, -GAME_PADDLE_MAX_SPEED);
		}
		else if(ballY > paddleCenterY)
		{
			m_Speed += GAME_PADDLE_ACCELERATION;
			m_Speed = MAX_VALUE(m_Speed, GAME_PADDLE_MAX_SPEED);
		}
		else
		{
			m_Speed = 0.0f;
		}
	}

	//Calculate the new y position value
	float newY = getY() + (m_Speed * aDelta);

	//Do some bounds checking on the new y position
	if(newY < 0.0f)
	{
		newY = 0.0f;
	}
	else if(newY + getHeight() > ScreenManager::getInstance()->getScreenHeight())
	{
		newY = ScreenManager::getInstance()->getScreenHeight() - getHeight();
	}

	//Set the paddle's new y position
	setY(newY);
}

void Paddle::paint()
{
	//Determine the color to draw the paddle, red for user controller, blue for computer controller
	if(m_ComputerControlled == false)
	{
		OpenGLRenderer::getInstance()->setForegroundColor(OpenGLColorRed());
	}
	else
	{
		OpenGLRenderer::getInstance()->setForegroundColor(OpenGLColorBlue());
	}

	//Draw the paddle with a black outline
	OpenGLRenderer::getInstance()->setLineWidth(2.0f);
	OpenGLRenderer::getInstance()->drawRectangle(getX(), getY(), getWidth(), getHeight());
	OpenGLRenderer::getInstance()->setForegroundColor(OpenGLColorBlack());
	OpenGLRenderer::getInstance()->drawRectangle(getX(), getY(), getWidth(), getHeight(), false);
	OpenGLRenderer::getInstance()->setLineWidth(1.0f);
}

void Paddle::reset()
{
	//Get the screen width and height
	float screenWidth = ScreenManager::getInstance()->getScreenWidth();
	float screenHeight = ScreenManager::getInstance()->getScreenHeight();

	//Reset the paddle's width and height
	setWidth(screenWidth * GAME_PADDLE_WIDTH_PERCENTAGE);
	setHeight(screenHeight * GAME_PADDLE_HEIGHT_PERCENTAGE);

	//Reset the x and y position
	setX((screenWidth * m_OffsetPercentageX) - (getWidth() / 2.0f));
	setY((screenHeight * GAME_PADDLE_Y_PERCENTAGE) - (getHeight() / 2.0f));

	//Reset the input flags
	m_UpArrowPressed = false;
	m_DownArrowPressed = false;

	//Reset the paddle's speed
	m_Speed = 0.0f;

	//Reset the paddle to active
	setIsActive(true);
}

const char* Paddle::getType()
{
	return GAME_PADDLE_TYPE;
}

void Paddle::keyUpEvent(int aKeyCode)
{
	if(m_ComputerControlled == false)
	{

		if(aKeyCode == KEYCODE_UP_ARROW)
		{
			m_UpArrowPressed = false;
		}
		else if(aKeyCode == KEYCODE_DOWN_ARROW)
		{
			m_DownArrowPressed = false;
		}
	}
	if(m_ComputerControlled == true)
	{
		if(aKeyCode == KEYCODE_W)
		{
			m_WPressed = false;
		}
		else if(aKeyCode == KEYCODE_S)
		{
			m_SPressed = false;
		}
	}
}

void Paddle::keyDownEvent(int aKeyCode)
{
	if(m_ComputerControlled == false)
	{
		if(aKeyCode == KEYCODE_UP_ARROW)
		{
			m_UpArrowPressed = true;
		}
		else if(aKeyCode == KEYCODE_DOWN_ARROW)
		{
			m_DownArrowPressed = true;
		}
	}
	if(m_ComputerControlled == true)
	{
		if(aKeyCode == KEYCODE_W)
		{
			m_WPressed = true;
		}
		else if(aKeyCode == KEYCODE_S)
		{
			m_SPressed = true;
		}
	}
}

void Paddle::setSize(float aWidth, float aHeight)
{
	setWidth(aWidth);
	setHeight(aHeight);
}

void Paddle::setWidth(float aWidth)
{
	m_Width = aWidth;
}

void Paddle::setHeight(float aHeight)
{
	m_Height = aHeight;
}

void Paddle::getSize(float &aWidth, float &aHeight)
{
	aWidth = getWidth();
	aHeight = getHeight();
}

float Paddle::getWidth()
{
	return m_Width;
}

float Paddle::getHeight()
{
	return m_Height;
}
void Paddle::setPlayer(bool player)
{
	m_Player = player;
}