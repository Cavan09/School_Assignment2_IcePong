#include "SubUIButton.h"
#include "UIButton.h"
#include "../OpenGL/OpenGL.h"
#include <stdlib.h>
#include <string>

SubUIButton::SubUIButton(const char* textureFile) : UIButton(textureFile),
	m_StateOne(NULL),
	m_StateTwo(NULL),
	m_StateThree(NULL),
	m_StateFour(NULL),
	m_CenterPositionY(0),
	m_CenterPositionX(0),
	m_Selected(1)
{
	m_StateOne = new OpenGLTexture(textureFile);
	std::string secondTextureFile = std::string(textureFile);
	secondTextureFile += "2";
	std::string thirdTextureFile = std::string(textureFile);
	thirdTextureFile += "3";
	std::string fourthTextureFile = std::string(textureFile);
	fourthTextureFile += "4";
	m_StateTwo = new OpenGLTexture(secondTextureFile.c_str());
	m_StateThree = new OpenGLTexture(thirdTextureFile.c_str());
	m_StateFour = new OpenGLTexture(fourthTextureFile.c_str());
}
SubUIButton::~SubUIButton()
{
	if(m_StateOne != NULL)
	{
		delete m_StateOne;
		m_StateOne = NULL;
	}
	if(m_StateTwo != NULL)
	{
		delete m_StateTwo;
		m_StateTwo = NULL;
	}
	if(m_StateThree != NULL)
	{
		delete m_StateThree;
		m_StateThree = NULL;
	}
	if(m_StateFour != NULL)
	{
		delete m_StateFour;
		m_StateFour = NULL;
	}
}
void SubUIButton::paint()
{
	if(getSelected() == 1)
	{
		float x = m_CenterPositionX;
		float y = m_CenterPositionY - m_StateOne->getSourceHeight() / 2.0f;
		OpenGLRenderer::getInstance()->drawTexture(m_StateOne,x,y);
	}
	else if(getSelected() == 2)
	{
		float x = m_CenterPositionX;
		float y = m_CenterPositionY - m_StateTwo->getSourceHeight() / 2.0f;
		OpenGLRenderer::getInstance()->drawTexture(m_StateTwo,x,y);
	}
	else if(getSelected() == 3)
	{
		float x = m_CenterPositionX;
		float y = m_CenterPositionY - m_StateThree->getSourceHeight() / 2.0f;
		OpenGLRenderer::getInstance()->drawTexture(m_StateThree,x,y);
	}
	else if(getSelected() == 4)
	{
		float x = m_CenterPositionX;
		float y = m_CenterPositionY - m_StateFour->getSourceHeight() / 2.0f;
		OpenGLRenderer::getInstance()->drawTexture(m_StateFour,x,y);
	}
	else if(getSelected() == 5)
	{
		setSelected(1);
	}

}
	void SubUIButton::setSelected(int selected)
	{
		m_Selected = selected;
	}
	int SubUIButton::getSelected()
	{
		return m_Selected;
	}
	void SubUIButton::setPosition(float centerX, float centerY)
	{
		m_CenterPositionX = centerX;
		m_CenterPositionY = centerY;
	}
	