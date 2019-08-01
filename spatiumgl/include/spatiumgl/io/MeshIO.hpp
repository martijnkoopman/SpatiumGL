/*
 * Program: Spatium Library
 *
 * Copyright (C) Martijn Koopman
 * All Rights Reserved
 *
 * This software is distributed WITHOUT ANY WARRANTY; without even
 * the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
 * PURPOSE.
 *
 */

#ifndef SPATIUMLIB_GFX3d_MESHIO_H
#define SPATIUMLIB_GFX3d_MESHIO_H

#include "TriangleMesh.h"

#include <fstream> // std::ofstream, std::ifstream
#include <sstream> // std::istringstream

namespace spatium {
namespace gfx3d {

/// \class MeshIO
/// \brief Read and write meshes
///
/// This class supports 1 file format:
///
/// - Wavefront Object (OBJ)
///   - http://paulbourke.net/dataformats/obj/
///   - Although this file format supports free-form geometry (curves,
///     surfaces), only polygonal geometry is read (points, lines, faces).
///
/// Beware! These functions have not been tested on endianness; big-endian vs
/// little-endian.
class MeshIO
{
public:
  /// Write mesh to file as OBJ (Wavefront Object).
  ///
  /// \param[in] mesh Mesh
  /// \param[in] objPath Path to PBM file. Should have file extension *.pbm
  /// \return True on success, false otherwise
  static bool writeMeshAsObj(const Mesh &mesh, const std::string &objPath)
  {
    std::ofstream ofile(objPath, std::ios::out);
    if (!ofile.is_open())
    {
      return false;
    }

    //mesh.vertex()

    ofile << "v 11 \n";

    return  true;
  }

  /// Read mesh from OBJ file (Wavefront Object).
  ///
  /// \param[in] objPath Path to OBJ file. Should have file extension *.obj
  /// \param[out] triangleMesh Triangle mesh
  /// \return True on success, false otherwise
  static bool readTriangleMeshFromObj(const std::string &objPath, TriangleMesh &triangleMesh)
  {
    // Open file
    std::ifstream ifile(objPath, std::ios::in);
    if (!ifile.is_open())
    {
      return false;
    }

    // Iterate lines
    std::string line;
    while (std::getline(ifile, line))
    {
      // Check line type
      std::istringstream iss(line);
      std::string linetype;
      iss >> linetype;

      if (linetype == "v") // Vertex
      {
        double x, y, z;
        iss >> x; ///\TODO Check failure iss.fail()
        iss >> y;
        iss >> z;

        triangleMesh.addVertex({x,y,z});
      }
      else if (linetype == "f") // Face
      {
        size_t v1, v2, v3;
        iss >> v1; ///\TODO Check failure iss.fail()
        iss >> v2;
        iss >> v3;

        triangleMesh.addTriangle({v1-1,v2-1,v3-1});
      }
    }

    return true;
  }

private:
  // Disable object instantiation
  MeshIO() = delete;
};

} // namespace gfx3d
} // namespace spatium

#endif // SPATIUMLIB_GFX3d_MESHIO_H
