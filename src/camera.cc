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
		}

	}
}

void Camera::leftClick(double x, double y) {
	if(!fps_mode) {
		
		if(!set_coord) 
		{
			cam_x = x;
			cam_y = y;
			set_coord = true;
		}
		else {
			float delta_x = cam_x - x;
			float delta_y = cam_y - y;
			glm::vec3 look = center_ - eye_;
			glm::vec3 horz = glm::cross(look, up_);
			//glm::mat3 vert = glm::mat3(glm::rotate(delta_x * pan_speed, up_)); 
			
			glm::mat3 horzRot = glm::mat3(glm::rotate(delta_y * pan_speed, horz));
			
			//eye_ = vert * eye_;
			//up_ = vert * up_;

			eye_ = horzRot * eye_;
			up_ = horzRot * up_;
			
			cam_y = y;
			cam_x = x;
		}

	}
	else {
		if(!set_coord) 
		{
			cam_x = x;
			cam_y = y;
			set_coord = true;
		}
		else {
			center_.x += (x - cam_x) * pan_speed;
			center_.y += (cam_y - y) * pan_speed;

			cam_y = y;
			cam_x = x;
		}
	}
}

void Camera::horizontalmvmt(int dir)
{
	glm::vec3 look = center_ - eye_;
	glm::vec3 side_dir = glm::normalize(glm::cross(up_, look));

	center_ += side_dir * (pan_speed * dir);
 	eye_ += side_dir * (pan_speed * dir);
}

void Camera::cameraRoll(int dir)
{
	up_ = glm::mat3( glm::rotate(dir * roll_speed, eye_)) * up_;
}

void Camera::verticalmvmt(int dir)
{
	eye_.z += dir * zoom_speed;
	center_.z += dir * zoom_speed;
}
void Camera::verticalmvmtArrows(int dir)
{
	center_ += up_ * (pan_speed * -dir);
 	eye_ += up_ * (pan_speed * -dir );
}

glm::mat4 Camera::get_view_matrix()
{
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
