#ifndef HAL_3DRENDERER_H_
#define HAL_3DRENDERER_H_

#ifdef __cplusplus
 extern "C" {
#endif

#include "tft_gui.h"

#include "math.h"
#include "fastMath.h"

typedef struct Vector3D {
	float x;
	float y;
	float z;
} Vector3D;

typedef float Matrix4x4[4][4];

void Init3DRenderer();
void GenerateRotaionMatrix(float x, float y, float z, Matrix4x4 *matrix);
Vector3D MulitplyMatrixVector(Vector3D vector, Matrix4x4 matrix);

void DrawMesh(Vector3D vertices[], uint16_t numVertices, uint16_t triangles[][3], uint16_t numTriangles);
void DrawCube();

#ifdef __cplusplus
}
#endif

#endif /* HAL_3DRENDERER_H_ */
