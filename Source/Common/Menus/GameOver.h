#ifndef GAMEOVER_H
#define GAMEOVER_H

#include "../Screen Manager/Screen.h"
#include "../UI/UIButton.h"
#include <vector>

class OpenGLTexture;

class GameOver : public Screen, public UIButtonListener
{
public:

	GameOver();
	~GameOver();

    const char* getName();
    void update(double delta);
    void paint();
	void keyUpEvent(int keyCode);
	void mouseMovementEvent(float deltaX, float deltaY, float positionX, float positionY);
	void mouseLeftClickUpEvent(float positionX, float positionY);
	void addUIButton(UIButton* aUIButton);
protected:
    void buttonAction(UIButton* button);
private:
	std::vector<UIButton*> m_Buttons;
	OpenGLTexture* m_Background;
	OpenGLTexture* m_Title;
	OpenGLTexture* m_WinOne;
	OpenGLTexture* m_WinTwo;
	OpenGLTexture* m_Tie;
	int m_Option;
};
#endif