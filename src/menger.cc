#include "menger.h"
#include <iostream>
namespace {
	const int kMinLevel = 0;
	const int kMaxLevel = 4;
};

Menger::Menger()
{
	// Add additional initialization if you like
}

Menger::~Menger()
{
}

void
Menger::set_nesting_level(int level)
{
	nesting_level_ = level;
	dirty_ = true;
}

bool
Menger::is_dirty() const
{
	return dirty_;
}

void
Menger::set_clean()
{
	dirty_ = false;
}

// FIXME generate Menger sponge geometry
void
Menger::generate_geometry(std::vector<glm::vec4>& obj_vertices,
                          std::vector<glm::uvec3>& obj_faces) 
{
	std::vector<glm::vec4> bounds;
	obj_vertices.clear();
	obj_faces.clear();
	bounds.push_back(glm::vec4(-0.5f, -0.5f, -0.5f, 1.0f));
	bounds.push_back(glm::vec4(0.5f, 0.5f, 0.5f, 1.0f));

	for(int i = 0; i < nesting_level_; i++)
	{
		CreateCube(bounds);
	}

	CreateMenger(obj_vertices, obj_faces, bounds);
	//std::cout << obj_vertices.size() << std::endl;
	//std::cout << obj_faces.size() << std::endl;
}

void Menger::CreateCube(std::vector<glm::vec4>& bounds) 
{
	std::vector<glm::vec4> temp;
	for(int i = 0; i < bounds.size(); i += 2) {
		double x_ratio = (bounds[i+1][0] - bounds[i][0]) / 3;
		double y_ratio = (bounds[i+1][1] - bounds[i][1]) / 3;
		double z_ratio = (bounds[i+1][2] - bounds[i][2]) / 3;
		
		glm::vec4 lower_bound(bounds[i]);
		glm::vec4 upper_bound(bounds[i + 1]);

		for(int x = 0; x < 3; ++x) {
			for(int y = 0; y < 3; ++y) {
				for(int z = 0; z < 3; ++z) {
					if( !((x == 1 && y == 1) || (y == 1 && z == 1) || (x == 1 && z == 1)) ) {
						lower_bound[0] += x_ratio * x;
						lower_bound[1] += y_ratio * y;
						lower_bound[2] += z_ratio * z;

						upper_bound[0] -= x_ratio * (2 - x);
						upper_bound[1] -= y_ratio * (2 - y);
						upper_bound[2] -= z_ratio * (2 - z);

						temp.push_back(lower_bound);
						temp.push_back(upper_bound);
						lower_bound = bounds[i];
						upper_bound = bounds[i + 1];
					}
				}
			}
		}
	}
	swap(bounds, temp);
}
//Need to implement this 
void 
Menger::CreateMenger(std::vector<glm::vec4>& obj_vertices,
                          std::vector<glm::uvec3>& indices,
                          std::vector<glm::vec4>& bounds)
{

	for(int i = 0; i < bounds.size(); i += 2) {
		glm::vec4 lower_bound = bounds[i];
		glm::vec4 upper_bound = bounds[i + 1];

		double xmin = lower_bound[0];
		double xmax = upper_bound[0];

		double ymin = lower_bound[1];
		double ymax = upper_bound[1];
		
		double zmin = lower_bound[2];
		double zmax = upper_bound[2];

		double s = indices.size() * 3;

		obj_vertices.push_back(glm::vec4(xmin, ymin, zmin, 1.0f));
		obj_vertices.push_back(glm::vec4(xmin, ymin, zmax, 1.0f));
		obj_vertices.push_back(glm::vec4(xmin, ymax, zmax, 1.0f));
		indices.push_back(glm::uvec3(s++, s++, s++));

		obj_vertices.push_back(glm::vec4(xmax, ymax, zmin, 1.0f));
		obj_vertices.push_back(glm::vec4(xmin, ymin, zmin, 1.0f));
		obj_vertices.push_back(glm::vec4(xmin, ymax, zmin, 1.0f));
		indices.push_back(glm::uvec3(s++, s++, s++));


		obj_vertices.push_back(glm::vec4(xmax, ymin, zmax, 1.0f));
		obj_vertices.push_back(glm::vec4(xmin, ymin, zmin, 1.0f));
		obj_vertices.push_back(glm::vec4(xmax, ymin, zmin, 1.0f));
		indices.push_back(glm::uvec3(s++, s++, s++));


		obj_vertices.push_back(glm::vec4(xmax, ymax, zmin, 1.0f));
		obj_vertices.push_back(glm::vec4(xmax, ymin, zmin, 1.0f));
		obj_vertices.push_back(glm::vec4(xmin, ymin, zmin, 1.0f));
		indices.push_back(glm::uvec3(s++, s++, s++));


		obj_vertices.push_back(glm::vec4(xmin, ymin, zmin, 1.0f));
		obj_vertices.push_back(glm::vec4(xmin, ymax, zmax, 1.0f));
		obj_vertices.push_back(glm::vec4(xmin, ymax, zmin, 1.0f));
		indices.push_back(glm::uvec3(s++, s++, s++));


		obj_vertices.push_back(glm::vec4(xmax, ymin, zmax, 1.0f));
		obj_vertices.push_back(glm::vec4(xmin, ymin, zmax, 1.0f));
		obj_vertices.push_back(glm::vec4(xmin, ymin, zmin, 1.0f));
		indices.push_back(glm::uvec3(s++, s++, s++));


		obj_vertices.push_back(glm::vec4(xmin, ymax, zmax, 1.0f));
		obj_vertices.push_back(glm::vec4(xmin, ymin, zmax, 1.0f));
		obj_vertices.push_back(glm::vec4(xmax, ymin, zmax, 1.0f));
		indices.push_back(glm::uvec3(s++, s++, s++));

		obj_vertices.push_back(glm::vec4(xmax, ymax, zmax, 1.0f));
		obj_vertices.push_back(glm::vec4(xmax, ymin, zmin, 1.0f));
		obj_vertices.push_back(glm::vec4(xmax, ymax, zmin, 1.0f));
		indices.push_back(glm::uvec3(s++, s++, s++));


		obj_vertices.push_back(glm::vec4(xmax, ymin, zmin, 1.0f));
		obj_vertices.push_back(glm::vec4(xmax, ymax, zmax, 1.0f));
		obj_vertices.push_back(glm::vec4(xmax, ymin, zmax, 1.0f));
		indices.push_back(glm::uvec3(s++, s++, s++));

		obj_vertices.push_back(glm::vec4(xmax, ymax, zmax, 1.0f));
		obj_vertices.push_back(glm::vec4(xmax, ymax, zmin, 1.0f));
		obj_vertices.push_back(glm::vec4(xmin, ymax, zmin, 1.0f));
		indices.push_back(glm::uvec3(s++, s++, s++));

		obj_vertices.push_back(glm::vec4(xmax, ymax, zmax, 1.0f));
		obj_vertices.push_back(glm::vec4(xmin, ymax, zmin, 1.0f));
		obj_vertices.push_back(glm::vec4(xmin, ymax, zmax, 1.0f));
		indices.push_back(glm::uvec3(s++, s++, s++));

		obj_vertices.push_back(glm::vec4(xmax, ymax, zmax, 1.0f));
		obj_vertices.push_back(glm::vec4(xmin, ymax, zmax, 1.0f));
		obj_vertices.push_back(glm::vec4(xmax, ymin, zmax, 1.0f));
		indices.push_back(glm::uvec3(s++, s++, s++));
	}
}
