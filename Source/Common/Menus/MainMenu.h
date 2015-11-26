#ifndef MAINMENU
#define MAINMENU

#include "../Screen Manager/Screen.h"
#include "../UI/UIButton.h"
#include <vector>

class MainMenu : public Screen, public UIButtonListener
{
public:

	MainMenu();
	~MainMenu();

    const char* getName();
    void update(double delta);
    void paint();
	void keyUpEvent(int keyCode);
	void mouseMovementEvent(float deltaX, float deltaY, float positionX, float positionY);
	void mouseLeftClickUpEvent(float positionX, float positionY);
	void addUIButton(UIButton* aUIButton);
	bool getMultiplayer();
protected:
    void buttonAction(UIButton* button);
private:
	std::vector<UIButton*> m_Buttons;
	int m_Option;
	bool m_Multiplayer;
	OpenGLTexture* m_Background;
	OpenGLTexture* m_Title;

};
#endif