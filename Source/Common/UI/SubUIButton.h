#ifndef SUBUIBUTTON_H
#define SUBUIBUTTON_H

#include "UIButton.h"

class OpenGLTexture;

class SubUIButton : public UIButton

{

public:

	SubUIButton(const char* textureFile);
	~SubUIButton();

	void paint();

	void setSelected(int selected);
	int getSelected();
	void setPosition(float centerX, float centerY);
	

private:
	int m_Selected;
	UIButtonListener* m_Listener;
	OpenGLTexture* m_StateOne;
	OpenGLTexture* m_StateTwo;
	OpenGLTexture* m_StateThree;
	OpenGLTexture* m_StateFour;

	float m_CenterPositionX;
	float m_CenterPositionY;

};
#endif
