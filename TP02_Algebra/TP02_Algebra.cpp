#include "raylib.h"

#include <iostream>
#include <vector>

using namespace std;

const int recSides = 8;

enum VERTEX_Z_POS
{
	IN,
	OUT
};

enum VERTEX_Y_POS
{
	UP,
	DOWN
};

enum VERTEX_X_POS
{
	RIGHT,
	LEFT
};

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

	VERTEX_X_POS posX = RIGHT;
	VERTEX_Y_POS posY = DOWN;
	VERTEX_Z_POS posZ = OUT;
};

struct Step
{
	VertexLines vertexLinesPos[recSides] = { };
};

const int windowWidth = 750;
const int windowHeight = 600;

void update(Camera3D& camera, vector<Step> steps);
void draw(Camera3D camera, vector<Step> steps, int amountOfVertexs);

void setVertexLines(VertexLines& vertexLines, float startingPosX, float startingPosY, float startingPosZ, float lenght);
void printVertexLines(VertexLines vertexLines[], int amountOfVertexs);
void setStep(VertexLines verLinesPos[], int amountOfVertexs, int randLength, int startingPosX, int startingPosY, int startingPosZ);

float vectorMagnitude(Vector3 v);

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

	Step basicStep = { };
	vector<Step> steps = { basicStep };

	int randLength = rand() % 20;
	int actualStep = 0;
	int totalSteps = 5;

	setStep(steps[actualStep].vertexLinesPos, recSides, randLength, 0, 0, 0);

	steps.push_back(basicStep);
	actualStep++;

	setStep(steps[actualStep].vertexLinesPos, recSides, randLength / 2, steps[actualStep - 1].vertexLinesPos[0].B.startingPos.x - (randLength / 4.0f), randLength / 4, steps[actualStep - 1].vertexLinesPos[0].C.startingPos.z - (randLength / 4.0f));

	SetTargetFPS(60);

	InitWindow(windowWidth, windowHeight, "Coso");

	while (!WindowShouldClose())
	{
		UpdateCamera(&camera, CAMERA_FREE);

		update(camera, steps);

		draw(camera, steps, recSides);
	}
}

void update(Camera3D& camera, vector<Step> steps)
{
	if (IsKeyPressed(KEY_Z))
		camera.position = { steps[0].vertexLinesPos[0].A.startingPos.x - 10, steps[0].vertexLinesPos[0].A.startingPos.y- 10, steps[0].vertexLinesPos[0].A.startingPos.z - 10 };

	// |A| = √(A_x² + A_y² + A_z²)
}

void draw(Camera3D camera, vector<Step> steps, int amountOfVertexs)
{
	BeginDrawing();

	BeginMode3D(camera);

	ClearBackground(BLACK);

	for (int i = 0; i < steps.size(); i++)
		printVertexLines(steps[i].vertexLinesPos, amountOfVertexs);
	
	//printVertexLines(vertexLines, amountOfVertexs);

	EndMode3D();

	DrawText(TextFormat("%02f", vectorMagnitude(steps[0].vertexLinesPos[0].C.startingPos)), 10, 10, 20, WHITE);
	DrawText(TextFormat("%02f", vectorMagnitude(steps[0].vertexLinesPos[0].C.endingPos)), 10, 40, 20, WHITE);

	EndDrawing();
}

void setVertexLines(VertexLines& vertexLines, float startingPosX, float startingPosY, float startingPosZ, float lenght)
{
	vertexLines.A.startingPos.x = startingPosX;
	vertexLines.A.startingPos.y = startingPosY;
	vertexLines.A.startingPos.z = startingPosZ;

	vertexLines.B.startingPos.x = startingPosX;
	vertexLines.B.startingPos.y = startingPosY;
	vertexLines.B.startingPos.z = startingPosZ;

	vertexLines.C.startingPos.x = startingPosX;
	vertexLines.C.startingPos.y = startingPosY;
	vertexLines.C.startingPos.z = startingPosZ;

	switch (vertexLines.posY)
	{
	case UP:

		vertexLines.A.endingPos.x = startingPosX;
		vertexLines.A.endingPos.y = startingPosY + (lenght / 2);
		vertexLines.A.endingPos.z = startingPosZ;

		break;
	case DOWN:

		vertexLines.A.endingPos.x = startingPosX;
		vertexLines.A.endingPos.y = startingPosY - (lenght / 2);
		vertexLines.A.endingPos.z = startingPosZ;

		break;
	default:
		break;
	}

	switch (vertexLines.posX)
	{
	case RIGHT:

		vertexLines.B.endingPos.x = startingPosX - (lenght * 2);
		vertexLines.B.endingPos.y = startingPosY;
		vertexLines.B.endingPos.z = startingPosZ;

		break;
	case LEFT:

		vertexLines.B.endingPos.x = startingPosX + (lenght * 2);
		vertexLines.B.endingPos.y = startingPosY;
		vertexLines.B.endingPos.z = startingPosZ;

		break;
	default:
		break;
	}

	switch (vertexLines.posZ)
	{
	case IN:

		vertexLines.C.endingPos.x = startingPosX;
		vertexLines.C.endingPos.y = startingPosY;
		vertexLines.C.endingPos.z = startingPosZ + lenght;

		break;
	case OUT:
		
		vertexLines.C.endingPos.x = startingPosX;
		vertexLines.C.endingPos.y = startingPosY;
		vertexLines.C.endingPos.z = startingPosZ - lenght;
		
		break;
	default:
		break;
	}
}

void printVertexLines(VertexLines vertexLines[], int amountOfVertexs)
{
	for (int i = 0; i < amountOfVertexs; i++)
	{
		DrawLine3D(vertexLines[i].A.startingPos, vertexLines[i].A.endingPos, RED);
		DrawLine3D(vertexLines[i].B.startingPos, vertexLines[i].B.endingPos, GREEN);
		DrawLine3D(vertexLines[i].C.startingPos, vertexLines[i].C.endingPos, BLUE);
	}
}

void setStep(VertexLines verLinesPos[], int amountOfVertexs, int randLength, int startingPosX, int startingPosY, int startingPosZ)
{
	for (int i = 0; i < amountOfVertexs; i++)
	{
		// A = Y || B = X || C = Z
		switch (i + 1)
		{
		case 1:

			setVertexLines(verLinesPos[i], startingPosX, startingPosY, startingPosZ, randLength);

			break;
		case 2:

			verLinesPos[i].posY = UP;

			setVertexLines(verLinesPos[i], verLinesPos[(i - 1)].A.endingPos.x, verLinesPos[(i - 1)].A.endingPos.y, verLinesPos[(i - 1)].A.endingPos.z, randLength);

			break;
		case 3:

			verLinesPos[i].posY = UP;
			verLinesPos[i].posX = LEFT;

			setVertexLines(verLinesPos[i], verLinesPos[(i - 1)].B.endingPos.x, verLinesPos[(i - 1)].B.endingPos.y, verLinesPos[(i - 1)].B.endingPos.z, randLength);

			break;
		case 4:

			verLinesPos[i].posY = DOWN;
			verLinesPos[i].posX = LEFT;

			setVertexLines(verLinesPos[i], verLinesPos[(i - 1)].A.endingPos.x, verLinesPos[(i - 1)].A.endingPos.y, verLinesPos[(i - 1)].A.endingPos.z, randLength);

			break;
		case 5:

			verLinesPos[i].posX = LEFT;
			verLinesPos[i].posZ = IN;

			setVertexLines(verLinesPos[i], verLinesPos[(i - 1)].C.endingPos.x, verLinesPos[(i - 1)].C.endingPos.y, verLinesPos[(i - 1)].C.endingPos.z, randLength);

			break;
		case 6:

			verLinesPos[i].posX = LEFT;
			verLinesPos[i].posY = UP;
			verLinesPos[i].posZ = IN;

			setVertexLines(verLinesPos[i], verLinesPos[(i - 1)].A.endingPos.x, verLinesPos[(i - 1)].A.endingPos.y, verLinesPos[(i - 1)].A.endingPos.z, randLength);

			break;
		case 7:

			verLinesPos[i].posY = UP;
			verLinesPos[i].posZ = IN;

			setVertexLines(verLinesPos[i], verLinesPos[(i - 1)].B.endingPos.x, verLinesPos[(i - 1)].B.endingPos.y, verLinesPos[(i - 1)].B.endingPos.z, randLength);

			break;
		case 8:

			verLinesPos[i].posZ = IN;

			setVertexLines(verLinesPos[i], verLinesPos[(i - 1)].A.endingPos.x, verLinesPos[(i - 1)].A.endingPos.y, verLinesPos[(i - 1)].A.endingPos.z, randLength);

			break;
		default:
			break;
		}
	}
}

float vectorMagnitude(Vector3 v)
{
	return sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);
}