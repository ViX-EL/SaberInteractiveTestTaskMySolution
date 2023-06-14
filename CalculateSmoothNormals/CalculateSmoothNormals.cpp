//
// Calculate smooth (average) per-vertex normals
//
// [out] normals - output per-vertex normals
// [in] verts - input per-vertex positions
// [in] faces - triangles (triplets of vertex indices)
// [in] nverts - total number of vertices (# of elements in verts and normals arrays)
// [in] nfaces - total number of faces (# of elements in faces array)
//

#include <cmath>
#include <exception>
#include <iostream>

struct vec3
{
    vec3(float value)
    {
        this->x = value;
        this->y = value;
        this->z = value;
    }

    vec3(float x, float y, float z)
    {
        this->x = x;
        this->y = y;
        this->z = z;
    }

    float x, y, z;

    vec3 operator-(const vec3& right) const
    {
        vec3 resVec(0.0f);
        resVec.x = this->x - right.x;
        resVec.y = this->y - right.y;
        resVec.z = this->z - right.z;
        return resVec;
    }

    vec3& operator+=(const vec3& right)
    {
        this->x += right.x;
        this->y += right.y;
        this->z += right.z;
		return *this;
    }
};

vec3 cross(const vec3& vect1, const vec3& vect2)
{
    vec3 resVec(0.0f);
    resVec.x = vect1.y * vect2.z - vect1.z * vect2.y;
    resVec.y = vect1.z * vect2.x - vect1.x * vect2.z;
    resVec.z = vect1.x * vect2.y - vect1.y * vect2.x;
    return resVec;
}

double length(const vec3& vec)
{
	double resLen = 0;
    resLen += pow(vec.x, 2);
    resLen += pow(vec.y, 2);
    resLen += pow(vec.z, 2);
	return resLen = sqrt(resLen);
}

vec3 normalize(const vec3& vec)
{
    try
    {
        double vecLength = length(vec);
        if (vecLength == 0)
            throw std::exception("For this operation, the vector length must not be zero!");
        vec3 resVec(0.0f);
        resVec.x = vec.y / vecLength;
        resVec.y = vec.z / vecLength;
        resVec.z = vec.x / vecLength;
        return resVec;
    }
    catch (const std::exception& ex)
    {
        std::cout << ex.what();
    }
}

void calc_mesh_normals(vec3* normals, const vec3* verts, const int* faces, int nverts, int nfaces) 
{
    for(int i = 0; i < nverts; i++) 
        normals[i] = vec3(0.0f);

    for(int i = 0; i < nfaces; i++)
    {
        int ia = faces[i*3+0];
        int ib = faces[i*3+1];
        int ic = faces[i*3+2];

        vec3 vect1 = verts[ia] - verts[ib];
        vec3 vect2 = verts[ic] - verts[ib];
        vec3 normal = cross(vect1, vect2);

        normals[ia] += normal;
        normals[ib] += normal;
        normals[ic] += normal;
    }

    for(int i = 0; i < nverts; i++) 
        normals[i] = normalize( normals[i]);
}