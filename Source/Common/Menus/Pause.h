#ifndef PAUSE_H
#define PAUSE_H

#include "../Screen Manager/Screen.h"
#include "../UI/UIButton.h"
#include <vector>

class OpenGLTexture;

class Pause : public Screen, public UIButtonListener
{
public:

	Pause();
	~Pause();

    const char* getName();
    void update(double delta);
    void paint();
	void keyUpEvent(int keyCode);
	void mouseMovementEvent(float deltaX, float deltaY, float positionX, float positionY);
	void mouseLeftClickUpEvent(float positionX, float positionY);
	void addUIButton(UIButton* aUIButton);
	bool getReturn();

protected:
    void buttonAction(UIButton* button);
private:
	std::vector<UIButton*> m_Buttons;
	OpenGLTexture* m_Background;
	OpenGLTexture* m_Title;
	UIButton* m_Resume;
	UIButton* m_Restart;
	UIButton* m_GameSettings;
	UIButton* m_MainMenu;
	int m_Option;
	bool m_Return;
	
};
#endif