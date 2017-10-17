#ifndef MENGER_H
#define MENGER_H

#include <glm/glm.hpp>
#include <vector>

class Menger {
public:
	Menger();
	~Menger();
	void set_nesting_level(int);
	bool is_dirty() const;
	void set_clean();
	void generate_geometry(std::vector<glm::vec4>& obj_vertices,
	                       std::vector<glm::uvec3>& obj_faces);
	void CreateMenger(std::vector<glm::vec4>& obj_vertices,
                          std::vector<glm::uvec3>& obj_faces,
                          std::vector<glm::vec4>& bounds);
	void set_save(bool flag);
	bool is_save();
	void CreateCube(std::vector<glm::vec4>& bounds);
private:
	int nesting_level_ = 0;
	bool dirty_ = false;
	bool save_ = false;
};
	
#endif
