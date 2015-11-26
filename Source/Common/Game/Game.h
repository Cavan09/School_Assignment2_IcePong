#ifndef GAME_H
#define GAME_H
#define NUMBER_TEXTURES_COUNT 10
#include <vector>
#include "../Screen Manager/Screen.h"

class GameObject;
class OpenGLTexture;

class Game : public Screen, public InputListener
{
public:
    Game();
    ~Game();
    
    //Game lifecycle methods
    void update(double delta);
    void paint();
    void reset();
    void resetVariables();
    //Game Over method, call this when to end the game
    void gameOver();
    void leftGoal();
    void rightGoal();
    
    //Screen name, must be implemented, it's a pure
    //virtual method in the Screen class
    const char* getName();
    
    //Screen event method, inherited from the screen class
    void screenWillAppear();
    
    //GameObject Methods
    void addGameObject(GameObject* gameObject);
    GameObject* getGameObjectByType(const char* type);
	void setControls(bool controls);
	void setSinglePlayer(bool SinglePlayer);
	void setScore(int score);
	bool getSinglePlayer();
	void setTimer(float time);
	float getTimer();
	int getWin();
	void setControlsTwo(bool control);
	bool getControlsTwo();
	bool getControls();
	
    
private:
    //Key Events
    void keyUpEvent(int keyCode);
    void keyDownEvent(int keyCode);
    void mouseMovementEvent(float deltaX, float deltaY, float positionX, float positionY);
	float drawNumber(int number, float x, float y);
    //Method to reset the ball, called after a goal is scored. The
    //parameter determines which direction the ball will go in
    //after a goal is scored.
    void resetBall(bool leftGoal);
    
    //Conveniance method used to paint the score info, drawn after
    //a goal is scored to update the user on the current score
    void paintScoreInfo(float alpha);
    
    //Vector to hold the GameObjects
    std::vector<GameObject*> m_GameObjects;
    
    //Texture's used for the score info
	OpenGLTexture* m_Numbers[NUMBER_TEXTURES_COUNT];
	OpenGLTexture* m_Colon;
    OpenGLTexture* m_AlgonquinLogo;
    OpenGLTexture* m_ScoreInfoBackground;
    OpenGLTexture* m_ScoreInfoGoal;
    OpenGLTexture* m_ScoreInfoLeft;
    OpenGLTexture* m_ScoreInfoRight;
    OpenGLTexture** m_ScoreInfoNumbers;
    
    //Score Info variables
    double m_ScoreInfoTimer;
    float m_ScoreInfoAlpha;
	float m_Timer;
	float m_GameTimer;
    
    //Score variables
    short m_LeftGoalsScored;
    short m_RightGoalsScored;

	bool m_Controls;
	bool m_ControlsTwo;
	bool m_SinglePlayer;
	int m_Score;
	int m_Win;
};

#endif