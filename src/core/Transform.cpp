#include "../core/Transform.h"

Transform::Transform(const glm::vec3& pos, const Quaternion& rot, float scale)
{
	m_pos = pos;
	m_rot = rot;
	m_scale = scale;
	m_initializedOldStuff = false;
	m_parent = 0;

	m_parentMatrix = glm::mat4()/*.InitIdentity()*/;
}

bool Transform::HasChanged()
{
	if (m_parent != 0 && m_parent->HasChanged())
		return true;

	if (m_pos != m_oldPos)
		return true;

	if (m_rot != m_oldRot)
		return true;

	if (m_scale != m_scale)
		return true;

	return false;
}

void Transform::Update()
{
	if (m_initializedOldStuff)
	{
		m_oldPos = m_pos;
		m_oldRot = m_rot;
		m_oldScale = m_scale;
	}
	else
	{
		m_oldPos = m_pos + glm::vec3(1, 1, 1);
		m_oldRot = m_rot * 0.5f;
		m_oldScale = m_scale + 1;
		m_initializedOldStuff = true;
	}
}

void Transform::Rotate(const glm::vec3& axis, float angle)
{
	Rotate(Quaternion(glm::angleAxis(angle,axis)));
}

void Transform::Rotate(const Quaternion& rotation)
{
	m_rot = Quaternion(glm::normalize((rotation * m_rot)));
}

void Transform::LookAt(const glm::vec3& point, const glm::vec3& up)
{
	m_rot = GetLookAtRotation(point, up);
}

glm::mat4 Transform::GetTransformation() const
{
	glm::mat4 translationMatrix;
	glm::mat4 scaleMatrix;

	Tools::initTranslation(translationMatrix,glm::vec3(m_pos.x, m_pos.y, m_pos.z));
	Tools::initScale(scaleMatrix, glm::vec3(m_scale, m_scale, m_scale));

	glm::mat4 result = translationMatrix * Tools::toRotationMatrix(m_rot) * scaleMatrix;

	return GetParentMatrix() * result;
}

glm::mat4 Transform::GetParentMatrix() const
{
	if (m_parent != 0 && m_parent->HasChanged())
		m_parentMatrix = m_parent->GetTransformation();

	return m_parentMatrix;
}
