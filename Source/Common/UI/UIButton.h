#ifndef UIBUTTON_H
#define UIBUTTON_H

class OpenGLTexture;
class UIButtonListener;
class UIButton

{
public:
	UIButton(const char* textureFile);
	~UIButton();

	virtual void paint();

	void mouseMovementEvent(float positionX, float positionY);
	void mouseLeftClickUpEvent(float positionX, float positionY);

	void keyLeftEvent(int aKeyCode);
	void keyRightEvent(int aKeyCode);

	void keyUpEvent(int aKeyCode);
	void keyDownEvent(int aKeyCode);

    void setListener(UIButtonListener* listener);
	virtual void setCenterPosition(float centerX, float centerY);
	void setRightPosition(float x, float y);
	void setIsSelected(bool IsSelected);
	bool getIsSelected();

protected:

	
private:
    UIButtonListener* m_Listener;
	OpenGLTexture* m_NormalState;
	OpenGLTexture* m_SelectedState;
	float m_CenterPositionX;
	float m_CenterPositionY;
	bool m_IsSelected;
	

};

class UIButtonListener
{
public:
    virtual void buttonAction(UIButton* button) = 0;
    
};
#endif