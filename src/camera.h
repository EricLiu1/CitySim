#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/rotate_vector.hpp>
class Camera {
public:
	glm::mat4 get_view_matrix(); // same as glm lookat
	// FIXME: add functions to manipulate camera objects.
	void horizontalmvmt(int dir);
	void cameraRoll(int dir);
	void verticalmvmt(int dir);
	void verticalmvmtArrows(int dir);
	bool getMode() { return fps_mode; };

	void switchMode() { fps_mode = !fps_mode; };
	void reset_coord() { set_coord = false; };

	void rightClick(double x, double y);
	void middleClick(double x, double y);
	void leftClick(double x, double y);
private:
	// load normally and transpose
	// matrix load by col not by rows
	void computeView();
	// we are recreating glm:lookat
	bool fps_mode = true;
	bool flag = false;
	glm::mat4 view;
	glm::vec3 center_ = glm::vec3(0.0f, 0.0f, 0.0f); // where it's looking at
	glm::vec3 up_ = glm::vec3(0.0f, 1.0, 0.0f);
	glm::vec3 eye_ = glm::vec3(0.0f, 0.0f, 3.0f); // position of camera
	// Note: you may need additional member variables
	bool set_coord = false;
	double cam_x = 0;
	double cam_y = 0;

};

#endif
