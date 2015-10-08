#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/quaternion.inl>
#include <glm/gtc/quaternion.hpp>
#include "../core/Tools.h"

class Transform
{
public:
	Transform(const glm::vec3& pos = glm::vec3(0, 0, 0), const Quaternion& rot = Quaternion(0, 0, 0, 1), float scale = 1.0f);

	glm::mat4 GetTransformation() const;
	bool HasChanged();
	void Update();
	void Rotate(const glm::vec3& axis, float angle);
	void Rotate(const Quaternion& rotation);
	void LookAt(const glm::vec3& point, const glm::vec3& up);

	Quaternion GetLookAtRotation(const glm::vec3& point, const glm::vec3& up)
	{
		glm::vec3 forward = point - m_pos;
		glm::vec3 n = glm::normalize(forward);
		glm::vec3 u = glm::cross(glm::normalize(up),n);
		glm::vec3 v = glm::cross(n,u);
		return Quaternion(Tools::initRotationFromVectors(n, u, v));
	}

	inline glm::vec3& GetPos() { return m_pos; }
	inline const glm::vec3& GetPos() const { return m_pos; }
	inline Quaternion& GetRot() { return m_rot; }
	inline const Quaternion& GetRot() const { return m_rot; }
	inline float GetScale() const { return m_scale; }

	inline glm::vec3 GetTransformedPos() const { return Tools::transformToVec3(GetParentMatrix(), m_pos); }
	inline Quaternion GetTransformedRot() const
	{
		Quaternion parentRot = Quaternion(0, 0, 0, 1);

		if (m_parent)
			parentRot = m_parent->GetTransformedRot();

		return parentRot * m_rot;
	}

	inline void SetPos(const glm::vec3& pos) { m_pos = pos; }
	inline void SetRot(const Quaternion& rot) { m_rot = rot; }
	inline void SetScale(float scale) { m_scale = scale; }
	inline void SetParent(Transform* parent) { m_parent = parent; }
protected:
private:
	glm::mat4 GetParentMatrix() const;

	glm::vec3 m_pos;
	Quaternion m_rot;
	float m_scale;

	Transform* m_parent;
	mutable glm::mat4 m_parentMatrix;

	mutable glm::vec3 m_oldPos;
	mutable Quaternion m_oldRot;
	mutable float m_oldScale;
	mutable bool m_initializedOldStuff;
};

#endif
