#include "raylib.h"

#include <iostream>
#include <vector>

using namespace std;

const int recSides = 8;

struct Line
{
	Vector3 startingPos = { };
	Vector3 endingPos = { };

	Color color = WHITE;
};

struct VertexLines
{
	Line A = { };
	Line B = { };
	Line C = { };
};

const int windowWidth = 750;
const int windowHeight = 600;

Line line1 = { };
Line line2 = { };
Line line3;

void update(Camera3D& camera);
void draw(Camera3D camera, VertexLines vertexLines, VertexLines vertexLines2);

void setVertexLines(VertexLines& vertexLines, float startingPosX, float startingPosY, float startingPosZ);
void printVertexLines(VertexLines vertexLines);

int main()
{
	srand(time(nullptr));

	Camera3D camera = { 0 };
	camera.position = { 0.0f, 00.0f, 10.0f };
	camera.target = { 0.0f, 0.0f, 0.0f };
	camera.up = { 0.0f, 1.0f, 0.0f };
	camera.fovy = 45.0f;
	camera.projection = CAMERA_PERSPECTIVE;

	//Line lineA = { {0,0,0}, {2,0,0}, RED };   // vector A
	//Line lineB = { {0,0,0}, {0,-2,0}, GREEN }; // vector B (90° en XY)

	int randStartingPos = rand() % 20;

	VertexLines verLinesPos = { };
	VertexLines verLinesPos2 = { };

	setVertexLines(verLinesPos, randStartingPos, randStartingPos, randStartingPos);
	setVertexLines(verLinesPos2, verLinesPos.A.endingPos.x, verLinesPos2.A.startingPos.y, verLinesPos2.A.startingPos.z);

	/*line1.startingPos = { float(randStartingPos), float(randStartingPos), float(randStartingPos) };
	line1.endingPos = { float(randStartingPos) * 2, float(randStartingPos) * 2, float(randStartingPos) * 2 };
	line2.startingPos = { line1.endingPos.x, line1.startingPos.y, line1.endingPos.z };
	line2.endingPos = { line1.endingPos.x * -1.0f, line1.endingPos.y, line1.endingPos.z * 2 };*/

	/*Vector3 A = line1.endingPos;
	Vector3 B = line2.endingPos;
	Vector3 C = { };*/

	/*C.x = A.y * B.z - A.z * B.y;
	C.y = A.z * B.x - A.x * B.z;
	C.z = A.x * B.y - A.y * B.x;*/

	//line3 = { {0,0,0}, C, WHITE };

	/*line.startingPos.x = 5 + rand() % 10;
	line.startingPos.y = 5 + rand() % 10;
	line.startingPos.z = 5 + rand() % 10;*/

	/*line.endingPos.x = line.startingPos.x + 10;
	line.endingPos.y = line.startingPos.y + 10;
	line.endingPos.z = line.startingPos.z + 10;*/

	SetTargetFPS(60);

	InitWindow(windowWidth, windowHeight, "Coso");

	while (!WindowShouldClose())
	{
		update(camera);

		draw(camera, verLinesPos, verLinesPos2);
	}
}

void update(Camera3D& camera)
{
	UpdateCamera(&camera, CAMERA_FREE);

	if (IsKeyPressed(KEY_Z))
		camera.position = { 10.0f, 10.0f, 10.0f };

	// |A| = √(A_x² + A_y² + A_z²)

	int line3Magnitud = line3.endingPos.x + line3.endingPos.y + line3.endingPos.z;
	cout << line3Magnitud << endl;
}

void draw(Camera3D camera, VertexLines vertexLines, VertexLines vertexLines2)
{
	BeginDrawing();

	BeginMode3D(camera);

	ClearBackground(BLACK);

	printVertexLines(vertexLines);
	printVertexLines(vertexLines2);

	/*DrawLine3D(vertexLines.A.startingPos, vertexLines.A.endingPos, vertexLines.A.color);
	DrawLine3D(vertexLines.B.startingPos, vertexLines.B.endingPos, vertexLines.B.color);
	DrawLine3D(vertexLines.C.startingPos, vertexLines.C.endingPos, vertexLines.C.color);*/

	//DrawLine3D(line1.startingPos, line1.endingPos, line1.color);
	//DrawLine3D(line2.startingPos, line2.endingPos, line1.color);
	//DrawLine3D(line3.startingPos, line3.endingPos, line1.color);

	EndMode3D();

	DrawText(TextFormat("%02f", camera.position.x), 10, 10, 20, WHITE);

	EndDrawing();
}

void setVertexLines(VertexLines& vertexLines, float startingPosX, float startingPosY, float startingPosZ)
{
	vertexLines.A.startingPos.x = startingPosX;
	vertexLines.A.startingPos.y = startingPosY;
	vertexLines.A.startingPos.z = startingPosZ;
	
	vertexLines.A.endingPos.x = startingPosX * 2;
	vertexLines.A.endingPos.y = startingPosY / 2;
	vertexLines.A.endingPos.z = startingPosZ * 2;

	vertexLines.B.startingPos.x = vertexLines.A.startingPos.x;
	vertexLines.B.startingPos.y = vertexLines.A.startingPos.y;
	vertexLines.B.startingPos.z = vertexLines.A.startingPos.z;

	vertexLines.B.endingPos.x = startingPosX / 2;
	vertexLines.B.endingPos.y = startingPosY * 2;
	vertexLines.B.endingPos.z = startingPosZ * 2;

	vertexLines.C.startingPos.x = vertexLines.A.startingPos.x;
	vertexLines.C.startingPos.y = vertexLines.A.startingPos.y;
	vertexLines.C.startingPos.z = vertexLines.A.startingPos.z;

	vertexLines.C.endingPos.x = startingPosX / 2;
	vertexLines.C.endingPos.y = startingPosY / 2;
	vertexLines.C.endingPos.z = startingPosZ * 2;
}

void printVertexLines(VertexLines vertexLines)
{
	DrawLine3D(vertexLines.A.startingPos, vertexLines.A.endingPos, vertexLines.A.color);
	DrawLine3D(vertexLines.B.startingPos, vertexLines.B.endingPos, vertexLines.B.color);
	DrawLine3D(vertexLines.C.startingPos, vertexLines.C.endingPos, vertexLines.C.color);
}

Vector3 Cross()
{
	return {
		//line1.y  line2.z - A.z  B.y,
		//A.z  B.x - A.x  B.z,
		//A.x  B.y - A.y  B.x
	};
}