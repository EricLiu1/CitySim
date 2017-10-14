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
	CreateCube(obj_vertices, obj_faces);
	for(int i = 0; i < 0; i++)
	{
		std::vector<glm::vec4> temp_vertices;
		for(int j = 0; j < obj_vertices.size(); ++j) {

			for(int x = 0; x < 3 ; ++x) 
			{
				for(int y = 0; y < 3; ++y) 
				{
					for(int z = 0; z < 3; ++z) 
					{
						glm::vec4 temp = obj_vertices[j];
						std:: cout << temp[0] << temp[1] << temp[2] << temp[3] << std::endl;
						if(x != y || y != z)
						{
							temp[0] += x * 0.33;
							temp[1] += y * 0.33;
							temp[2] += z * 0.33;
							temp_vertices.push_back(temp);
						}
					}
				}
			}
		}
		std::cout << obj_vertices.size();
		swap(obj_vertices, temp_vertices);
 	}
}
void Menger::CreateCube(std::vector<glm::vec4>& obj_vertices,
                          std::vector<glm::uvec3>& indices) 
{
	return;
}
//Need to implement this 
void 
Menger::CreateMenger()
{

}
