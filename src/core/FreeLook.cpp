#include "../core/FreeLook.h"
#include "../core/Tools.h"
#include "../core/Window.h"

bool mouseLocked = false;

FreeLook::FreeLook(float sensitivity, int unlockMouseKey)
{
	m_sensitivity = sensitivity;
	m_unlockMouseKey = unlockMouseKey;
}

void FreeLook::Input(float delta)
{
	if(Input::GetKey(m_unlockMouseKey))
	{
		Input::SetCursor(true);
		mouseLocked = false;
	}

	if(mouseLocked)
	{
		glm::vec2 centerPosition = glm::vec2((float)Window::GetWidth()/2.0f, (float)Window::GetHeight()/2.0f);
		glm::vec2 deltaPos = Input::GetMousePosition() - centerPosition;
		
		bool rotY = deltaPos.x!= 0;
		bool rotX = deltaPos.y != 0;
			
		if(rotY)
			GetTransform().Rotate(glm::vec3(0,1,0), ToRadians(deltaPos.x * m_sensitivity));
		if(rotX)
			GetTransform().Rotate(Tools::GetRight(GetTransform().GetRot()), ToRadians(deltaPos.y * m_sensitivity));
			
		if(rotY || rotX)
			Input::SetMousePosition(centerPosition);
	}

	if(Input::GetMouseDown(Input::LEFT_MOUSE))
	{
		glm::vec2 centerPosition = glm::vec2((float)Window::GetWidth()/2.0f, (float)Window::GetHeight()/2.0f);
		Input::SetCursor(false);
		Input::SetMousePosition(centerPosition);
		mouseLocked = true;
	}
}
