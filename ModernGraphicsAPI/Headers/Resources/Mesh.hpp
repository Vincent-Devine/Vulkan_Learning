#pragma once

#include <string>
#include <vector>

#include "Common.hpp"

namespace Resources
{
    class Mesh
    {
        // ----------
        // Attributes
        // ----------
    public:
        std::vector<Vertex> vertices;
        std::vector<uint32_t> indices;

    private:
        std::string path;

        // -------
        // Methods
        // -------
    public:
        void Init(const std::string& p_path);

    private:
        void LoadMesh();
        void SetCube();
    };
}