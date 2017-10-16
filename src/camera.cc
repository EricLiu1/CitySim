#include "camera.h"
#include <iostream>

namespace {
	float pan_speed = 0.1f;
	float roll_speed = 0.1f;
	float rotation_speed = 0.05f;
	float zoom_speed = 0.1f;
};

void Camera::rightClick(double x, double y) {
	if(fps_mode) {
		
		if(!set_coord) 
		{
			cam_x = x;
			cam_y = y;
			set_coord = true;
		}
		else {
			eye_.z += (cam_y - y) * zoom_speed;
			center_.z += (cam_y - y) * zoom_speed;
			
			cam_y = y;
			cam_x = x;
			
			flag = false;
		}

	}
}

void Camera::horizontalmvmt(int dir, bool fps)
{
	center_.x += dir * pan_speed;
 	eye_.x += dir * pan_speed;
 	flag = false;
}

void Camera::cameraRoll(int dir)
{
	view *= glm::rotate(dir * roll_speed, eye_);
}

void Camera::verticalmvmt(int dir, bool fps)
{
	eye_.z += dir * zoom_speed;
	center_.z += dir * zoom_speed;
	flag = false;
}
void Camera::verticalmvmtArrows(int dir, bool fps)
{
	center_.y += dir * pan_speed;
	eye_.y += dir * pan_speed;
	flag = false;
}

glm::mat4 Camera::get_view_matrix()
{

	if(flag)
		return view;

	flag = true;
	computeView();

	return view;
}

void Camera::computeView() {

	glm::vec3 x, y, z;
	z = eye_ - center_;
	z = glm::normalize(z);

	x = glm::cross(up_, z);
	y = glm::cross(z, x);

	x = glm::normalize(x);
	y = glm::normalize(y);

	view[0][0] = x[0];
	view[1][0] = x[1];
	view[2][0] = x[2];
	view[3][0] = -glm::dot(x, eye_);

	view[0][1] = y[0];
	view[1][1] = y[1];
	view[2][1] = y[2];
	view[3][1] = -glm::dot(y, eye_);

	view[0][2] = z[0];
	view[1][2] = z[1];
	view[2][2] = z[2];
	view[3][2] = -glm::dot(z, eye_);
}
