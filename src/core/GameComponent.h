#ifndef GAMECOMPONENT_H
#define GAMECOMPONENT_H

#include "../core/Transform.h"
#include "../core/GameObject.h"

class RenderingEngine;
class Shader;

class GameComponent
{
public:
	virtual ~GameComponent() {}

	virtual void Input(float delta) {}
	virtual void Update(float delta) {}
	virtual void Render(Shader* shader, RenderingEngine* renderingEngine) {}
	
	virtual void AddToEngine(CoreEngine* engine) { }
	
	inline void SetParent(GameObject* parent) { m_parent = parent; }
	inline Transform& GetTransform() { return m_parent->GetTransform(); }
	inline const Transform& GetTransform() const { return m_parent->GetTransform(); }
	
private:
	GameObject* m_parent;
};

#endif // GAMECOMPONENT_H_INCLUDED
