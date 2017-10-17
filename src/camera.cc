#include "camera.h"
#include <iostream>

namespace {
	float pan_speed = 0.05f;
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
			eye_.z += (y - cam_y) * zoom_speed;
			center_.z += (y - cam_y) * zoom_speed;
			
			cam_y = y;
			cam_x = x;
			
			flag = false;
		}

	}
}

void Camera::middleClick(double x, double y) {
	if(fps_mode) {
		
		if(!set_coord) 
		{
			cam_x = x;
			cam_y = y;
			set_coord = true;
		}
		else {
			// std::cout << "up " << up_[0] << " " << up_[1] << " " << up_[2] << std::endl;
			// std::cout << "center " << center_[0] << " " << center_[1] << " " << center_[2] << std::endl;
			// std::cout << "eye " << eye_[0] << " " << eye_[1] << " " << eye_[2] << std::endl;

			center_.x += (x - cam_x) * pan_speed;
		 	eye_.x += (x - cam_x) * pan_speed;
		 	//up_.x += (x - cam_x) * pan_speed;

			center_.y += (cam_y - y) * pan_speed;
			eye_.y += (cam_y - y) * pan_speed;
			//up_.y += (cam_y - y) * pan_speed;

			cam_y = y;
			cam_x = x;
			flag = false;


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
			glm::vec3 horizontal_vector = glm::cross(center_ - eye_, up_);
			glm::vec3 vertical_vector = glm::cross(eye_ - center_, horizontal_vector);
			float delta_x = x - cam_x;
			float delta_y = y - cam_y;
			//glm::vec4 up2_ = glm::vec4(up_[0], up_[1],up_[2], 1.0f);
			view *= glm::rotate( delta_y * pan_speed, horizontal_vector) * glm::rotate( delta_x * pan_speed, up_ );
			//up2_ = glm::rotate( delta_y * pan_speed, horizontal_vector ) * up2_;
			
			//view *= glm::rotate( delta_x * pan_speed, up_ );
			// up2_ = glm::rotate( delta_x * pan_speed, vertical_vector ) * up2_;
			// up_[0] = up2_[0];
			// up_[1] = up2_[1];
			// up_[2] = up2_[2];

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
		else 
		{
			center_.x += (x - cam_x) * pan_speed;
			center_.y += (cam_y - y) * pan_speed;
			cam_y = y;
			cam_x = x;

			flag = false;
		}
	}
}


void Camera::horizontalmvmt(int dir)
{
	center_.x += dir * pan_speed;
 	eye_.x += dir * pan_speed;
 	flag = false;
}

void Camera::cameraRoll(int dir)
{
	view *= glm::rotate(dir * roll_speed, eye_);
	// up_[0] = view[0][1];
	// up_[1] = view[1][1];
	// up_[2] = view[2][1];
}

void Camera::verticalmvmt(int dir)
{
	eye_.z += dir * zoom_speed;
	center_.z += dir * zoom_speed;
	flag = false;
}
void Camera::verticalmvmtArrows(int dir)
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
	// std::cout << view[0][0] << " " << view[0][1] << " " << view[0][2] << " " << view[0][3] << std::endl;
	// std::cout << view[1][0] << " " << view[1][1] << " " << view[1][2] << " " << view[1][3] << std::endl;
	// std::cout << view[2][0] << " " << view[2][1] << " " << view[2][2] << " " << view[2][3] << std::endl;
	// std::cout << view[3][0] << " " << view[3][1] << " " << view[3][2] << " " << view[3][3] << std::endl;
}
