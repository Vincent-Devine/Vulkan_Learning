#include "Mesh.hpp"

#define TINYOBJLOADER_IMPLEMENTATION
#include <tiny_obj_loader.h>

#include "Assertion.hpp"

namespace Resources
{
    void Mesh::Init(const std::string& p_path)
    {
        path = p_path;
        LoadMesh();
    }

    void Mesh::LoadMesh()
    {
        tinyobj::attrib_t attrib;
        std::vector<tinyobj::shape_t> shapes;
        std::vector<tinyobj::material_t> materials;
        std::string warn, err;

        Assertion(tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, path.c_str()) == true, warn + err);

        for (const auto& shape : shapes)
        {
            for (const auto& index : shape.mesh.indices)
            {
                Vertex vertex{};

                vertex.pos =
                {
                    attrib.vertices[3 * index.vertex_index + 0],
                    attrib.vertices[3 * index.vertex_index + 1],
                    attrib.vertices[3 * index.vertex_index + 2]
                };

                vertex.texCoord =
                {
                    attrib.texcoords[2 * index.texcoord_index + 0],
                    1.0f - attrib.texcoords[2 * index.texcoord_index + 1]
                };

                vertex.color = { 1.0f, 1.0f, 1.0f };

                vertices.push_back(vertex);
                indices.push_back(indices.size());
            }
        }
    }
}