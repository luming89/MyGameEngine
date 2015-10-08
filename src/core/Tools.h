#ifndef TOOLS_H
#define TOOLS_H

#define MATH_PI 3.1415926535897932384626433832795
#define ToRadians(x) (float)(((x) * MATH_PI / 180.0f))
#define ToDegrees(x) (float)(((x) * 180.0f / MATH_PI))

typedef glm::detail::tquat<float, glm::precision::highp> Quaternion;

namespace Tools
{
	glm::mat4 initRotationFromVectors(const glm::vec3& n, const glm::vec3& v, const glm::vec3& u) // forward, up, right
	{
		glm::mat4 res; // Identity?
		res[0][0] = u.x;   res[1][0] = u.y;   res[2][0] = u.z;   res[3][0] = 0;
		res[0][1] = v.x;   res[1][1] = v.y;   res[2][1] = v.z;   res[3][1] = 0;
		res[0][2] = n.x;   res[1][2] = n.y;   res[2][2] = n.z;   res[3][2] = 0;
		res[0][3] = 0;       res[1][3] = 0;       res[2][3] = 0;       res[3][3] = 1;
		return res;
	}

	glm::vec3 transformToVec3(const glm::mat4& m, const glm::vec3& r)
	{
		glm::vec3 ret;

		for (unsigned int i = 0; i < 3; i++)
		{
			ret[i] = 0;
			for (unsigned int j = 0; j < 3; j++)
				ret[i] += m[j][i] * r[j];
		}

		return ret;
	}

	glm::vec3 GetRight(const Quaternion r)
	{
		return glm::rotate(r, glm::vec3(1, 0, 0));
	}

	glm::mat4 initTranslation(glm::mat4& m, const glm::vec3& r)
	{
		for (unsigned int i = 0; i < 4; i++)
		{
			for (unsigned int j = 0; j < 4; j++)
			{
				if (i == 3 && j != 3)
					m[i][j] = r[j];
				else if (i == j)
					m[i][j] = 1;
				else
					m[i][j] = 0;
			}
		}
		m[3][3] = 1;
		return m;
	}

	glm::mat4 initScale(glm::mat4& m, const glm::vec3& r)
	{
		for (unsigned int i = 0; i < 4; i++)
		{
			for (unsigned int j = 0; j < 4; j++)
			{
				if (i == j && i != 3)
					m[i][j] = r[i];
				else
					m[i][j] = 0;
			}
		}

		m[3][3] = 1;

		return m;
	}

	glm::mat4 toRotationMatrix(const Quaternion& rot)
	{
		glm::vec3 forward = glm::vec3(2.0f * (rot.x * rot.z - rot.w * rot.y), 2.0f * (rot.y * rot.z + rot.w * rot.x), 1.0f - 2.0f * (rot.x * rot.x + rot.y * rot.y));
		glm::vec3 up = glm::vec3(2.0f * (rot.x*rot.y + rot.w*rot.z), 1.0f - 2.0f * (rot.x*rot.x + rot.z*rot.z), 2.0f * (rot.y*rot.z - rot.w*rot.x));
		glm::vec3 right = glm::vec3(1.0f - 2.0f * (rot.y*rot.y + rot.z*rot.z), 2.0f * (rot.x*rot.y - rot.w*rot.z), 2.0f * (rot.x*rot.z + rot.w*rot.y));

		return initRotationFromVectors(forward, up, right);
	}
}

#endif