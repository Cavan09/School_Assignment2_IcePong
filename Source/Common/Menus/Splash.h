#ifndef SPLASH
#define SPLASH

#include "../Screen Manager/Screen.h"
#include "../UI/UIButton.h"

class OpenGLTexture;

class Splash : public Screen, public UIButtonListener
{
public:

	Splash();
	~Splash();

    const char* getName();
    void update(double delta);
    void paint();
	void keyUpEvent(int keyCode);
	void mouseMovementEvent(float deltaX, float deltaY, float positionX, float positionY);
	void mouseLeftClickUpEvent(float positionX, float positionY);
protected:
    void buttonAction(UIButton* button);
private:
	OpenGLTexture* m_Background;
	OpenGLTexture* m_Title;
	UIButton* m_PressSpace;
};
#endif