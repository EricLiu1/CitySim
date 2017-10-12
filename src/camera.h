#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera {
public:
	glm::mat4 get_view_matrix() const; // same as glm lookat
	// FIXME: add functions to manipulate camera objects.
	void horizontalmvmt(int dir, bool fps);
	void verticalmvmtArrows(int dir, bool fps);
	bool getMode() { return fps_mode; };
	void switchMode() { fps_mode = !fps_mode; };

private:
	// load normally and transpose
	// matrix load by col not by rows

	// we are recreating glm:lookat
	bool fps_mode = false;
	glm::vec3 center_ = glm::vec3(0.0f, 0.0f, 0.0f); // where it's looking at
	glm::vec3 up_ = glm::vec3(0.0f, 1.0, 0.0f);
	glm::vec3 eye_ = glm::vec3(0.0f, 0.0f, 3.0f); // position of camera
	// Note: you may need additional member variables
};

#endif
