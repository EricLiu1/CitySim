#include "camera.h"
#include <iostream>

namespace {
	float pan_speed = 0.1f;
	float roll_speed = 0.1f;
	float rotation_speed = 0.05f;
	float zoom_speed = 0.1f;
};

void Camera::horizontalmvmt(int dir, bool fps)
{
	center_.x += dir * pan_speed;
	// eye_.z = direction * pan_speed;
	if(fps)
	{
		eye_.x += dir * pan_speed;


	}

}
void Camera::verticalmvmt(int dir, bool fps)
{
//	eye_.x += dir * zoom_speed;
//	eye_.y += dir * zoom_speed;
	eye_.z += dir * zoom_speed;


	// eye_.z = direction * pan_speed;
	if(fps)
	{
//		center_.x += dir * zoom_speed;
//		center_.y += dir * zoom_speed;
		center_.z += dir * zoom_speed;


	}

}
void Camera::verticalmvmtArrows(int dir, bool fps)
{
	center_.y += dir * pan_speed;

	// eye_.z = direction * pan_speed;
	if(fps)
	{
		eye_.y += dir * pan_speed;

	}
	
}
// FIXME: Calculate the view matrix
glm::mat4 Camera::get_view_matrix() const
{
	//glm::mat4 ans = glm::lookAt(eye_, center_, up_);

	glm::vec3 x, y, z;

	z = eye_ - center_;
	z = glm::normalize(z);

	x = glm::cross(up_, z);
	y = glm::cross(z, x);

	x = glm::normalize(x);
	y = glm::normalize(y);

	glm::mat4 gg;
	gg[0][0] = x[0];
	gg[1][0] = x[1];
	gg[2][0] = x[2];
	gg[3][0] = -glm::dot(x, eye_);

	gg[0][1] = y[0];
	gg[1][1] = y[1];
	gg[2][1] = y[2];
	gg[3][1] = -glm::dot(y, eye_);

	gg[0][2] = z[0];
	gg[1][2] = z[1];
	gg[2][2] = z[2];
	gg[3][2] = -glm::dot(z, eye_);
	return gg;
}
