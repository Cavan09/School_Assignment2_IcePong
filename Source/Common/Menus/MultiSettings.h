#ifndef MULTISETTINGS_H
#define MULTISETTINGS_H

#include "../Screen Manager/Screen.h"
#include "../UI/UIButton.h"
#include "../UI/SubUIButton.h"
#include <vector>

class OpenGLTexture;

class MultiSettings : public Screen, public UIButtonListener
{
public:

	MultiSettings();
	~MultiSettings();

    const char* getName();
    void update(double delta);
    void paint();
	void keyUpEvent(int keyCode);
	void mouseMovementEvent(float deltaX, float deltaY, float positionX, float positionY);
	void mouseLeftClickUpEvent(float positionX, float positionY);
	void addUIButton(UIButton* aUIButton);
	void addSubUIButton(SubUIButton* aSubUIButton);
protected:
    void buttonAction(UIButton* button);
private:
	std::vector<UIButton*> m_Buttons;
	std::vector<SubUIButton*> m_Settings;
	OpenGLTexture* m_Background;
	OpenGLTexture* m_Title;
	int m_Option;
	int m_SelectScore;
	int m_SelectTime;
	int m_SelectAi;
	int m_SelectInput;
	
};
#endif