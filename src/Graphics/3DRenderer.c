#include "3DRenderer.h"

#include "deadmou5Head.h"

Vector3D cube[8] = {{-0.5,0.5,-0.5},
					{-0.5,0.5,0.5},
					{0.5,0.5,0.5},
					{0.5,0.5,-0.5},
					{-0.5,-0.5,-0.5},
					{-0.5,-0.5,0.5},
					{0.5,-0.5,0.5},
					{0.5,-0.5,-0.5}};

uint16_t cubeTriangles[12][3] = {{1,2,3},
								{4,1,3},
								{2,6,7},
								{7,3,2},
								{2,6,5},
								{5,1,2},
								{3,8,4},
								{3,7,8},
								{5,6,7},
								{7,8,5},
								{1,5,8},
								{8,4,1}};

Matrix4x4 projectionMatrix;
Matrix4x4 matrixRotation;

void DrawCube() {
//	DrawMesh(vertices, 352, triangles, 684);
	DrawMesh(cube, 8, cubeTriangles, 12);
}

float fTheta = 0;
void DrawMesh(Vector3D vertices[], uint16_t numVertices, uint16_t triangles[][3], uint16_t numTriangles) {
	Color color = {50, 205, 50};
	Color colorBlack = {0x00, 0x00, 0x00};
	Vector3D rotationVector;
	Vector3D translatedVector3D;

	Vector3D drawMesh[500];

	fTheta -= 6;

	if(fTheta <= 0) {
		fTheta = 360;
	}

	GenerateRotaionMatrix(180, 0, fTheta, &matrixRotation);

	Vector2D projectedVector2DA;
	Vector2D projectedVector2DB;
	Vector2D projectedVector2DC;

	//Draw Vertices Points
	uint16_t i;
	for(i = 0; i < numVertices; i++) {
		projectedVector2DA.x = (drawMesh[i].x + 1) * 0.5f * SCREEN_WIDTH;
		projectedVector2DA.y = (drawMesh[i].y + 1) * 0.5f * SCREEN_HEIGHT;
		SetPixel(projectedVector2DA, colorBlack);

		rotationVector = MulitplyMatrixVector(vertices[i], matrixRotation);

		translatedVector3D = rotationVector;
		translatedVector3D.z += 3.0f;			//Set object away from the "camera"

		drawMesh[i] = MulitplyMatrixVector(translatedVector3D, projectionMatrix);

		projectedVector2DA.x = (drawMesh[i].x + 1) * 0.5f * SCREEN_WIDTH;
		projectedVector2DA.y = (drawMesh[i].y + 1) * 0.5f * SCREEN_HEIGHT;

		SetPixel(projectedVector2DA, ToRGB666Convertion(color));
	}

	//Draw Connecting Edges
	for(i = 0; i < numTriangles; i++) {
		projectedVector2DA.x = (drawMesh[triangles[i][0] - 1].x + 1) * 0.5f * SCREEN_WIDTH;
		projectedVector2DA.y = (drawMesh[triangles[i][0] - 1].y + 1) * 0.5f * SCREEN_HEIGHT;

		projectedVector2DB.x = (drawMesh[triangles[i][1] - 1].x + 1) * 0.5f * SCREEN_WIDTH;
		projectedVector2DB.y = (drawMesh[triangles[i][1] - 1].y + 1) * 0.5f * SCREEN_HEIGHT;

		projectedVector2DC.x = (drawMesh[triangles[i][2] - 1].x + 1) * 0.5f * SCREEN_WIDTH;
		projectedVector2DC.y = (drawMesh[triangles[i][2] - 1].y + 1) * 0.5f * SCREEN_HEIGHT;

		DrawLine(projectedVector2DA, projectedVector2DB, color);
		DrawLine(projectedVector2DB, projectedVector2DC, color);
		DrawLine(projectedVector2DC, projectedVector2DA, color);
	}
}

void Init3DRenderer() {
	float fAspectRatio = (float)SCREEN_HEIGHT / SCREEN_WIDTH;
	float fFov = 90.0f;
	float fFovRad = 1.0f / tanf(fFov * 0.5f / 180.0f * 3.14159f);
	float fNear = 0.1f;
	float fFar = 1000;

	projectionMatrix[0][0] = fAspectRatio * fFovRad;
	projectionMatrix[0][1] = 0;
	projectionMatrix[0][2] = 0;
	projectionMatrix[0][3] = 0;
	projectionMatrix[1][0] = 0;
	projectionMatrix[1][1] = fFovRad;
	projectionMatrix[1][2] = 0;
	projectionMatrix[1][3] = 0;
	projectionMatrix[2][0] = 0;
	projectionMatrix[2][1] = 0;
	projectionMatrix[2][2] = fFar / (fFar - fNear);
	projectionMatrix[2][3] = 1.0f;
	projectionMatrix[3][0] = 0;
	projectionMatrix[3][1] = 0;
	projectionMatrix[3][2] = (-fFar * fNear) / (fFar - fNear);
	projectionMatrix[3][3] = 0;
}

void GenerateRotaionMatrix(float roll, float pitch, float yaw, Matrix4x4 *matrix) {
	float s_y = FastSin(yaw * 0.5);
	float c_y = FastCos(yaw * 0.5);
	float s_p = FastSin(pitch * 0.5);
	float c_p = FastCos(pitch * 0.5);
	float s_r = FastSin(roll * 0.5);
	float c_r = FastCos(roll * 0.5);

//	float s_y = arm_sin_f32((yaw * 0.5) * 0.0174533);
//	float c_y = arm_cos_f32((yaw * 0.5) * 0.0174533);
//	float s_p = arm_sin_f32((pitch * 0.5) * 0.0174533);
//	float c_p = arm_cos_f32((pitch * 0.5) * 0.0174533);
//	float s_r = arm_sin_f32((roll * 0.5) * 0.0174533);
//	float c_r = arm_cos_f32((roll * 0.5) * 0.0174533);

	float x = c_y * s_p * c_r + s_y * c_p * s_r;
	float y = s_y * c_p * c_r - c_y * s_p * s_r;
	float z = c_y * c_p * s_r - s_y * s_p * c_r;
	float w = c_y * c_p * c_r + s_y * s_p * s_r;

	(*matrix)[0][0] = 1.0 - (2.0 * (y * y + z * z));
	(*matrix)[0][1] = 2.0 * (x * y + z * w);
	(*matrix)[0][2] = 2.0 * (z * x - y * w);
	(*matrix)[0][3] = 0;
	(*matrix)[1][0] = 2.0 * (x * y - z * w);
	(*matrix)[1][1] = 1.0 - (2.0 * (z * z + x * x));
	(*matrix)[1][2] = 2.0 * (y * z + x * w);
	(*matrix)[1][3] = 0;
	(*matrix)[2][0] = 2.0 * (z * x + y * w);
	(*matrix)[2][1] = 2.0 * (y * z - x * w);
	(*matrix)[2][2] = 1.0 - (2.0 * (y * y + x * x));
	(*matrix)[2][3] = 0;
	(*matrix)[3][0] = 0;
	(*matrix)[3][1] = 0;
	(*matrix)[3][2] = 0;
	(*matrix)[3][3] = 1;
}

Vector3D MulitplyMatrixVector(Vector3D vector, Matrix4x4 matrix) {
	Vector3D outputVector;

	outputVector.x = vector.x * matrix[0][0] + vector.y * matrix[1][0] + vector.z * matrix[2][0] + matrix[3][0];
	outputVector.y = vector.x * matrix[0][1] + vector.y * matrix[1][1] + vector.z * matrix[2][1] + matrix[3][1];
	outputVector.z = vector.x * matrix[0][2] + vector.y * matrix[1][2] + vector.z * matrix[2][2] + matrix[3][2];
	float w = vector.x * matrix[0][3] + vector.y * matrix[1][3] + vector.z * matrix[2][3] + matrix[3][3];

	if(w != 0) {
		outputVector.x /= w;
		outputVector.y /= w;
		outputVector.z /= w;
	}

	return outputVector;
}
