#include <stdio.h>
#include "Z:\raylib\raylib\src\raylib.h"
#include "Z:\raylib\raylib\src\rlgl.h"
#include "Z:\raylib\raylib\src\raymath.h"
#include <time.h> //Задержка по времени тут!!!	


const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 800;

const int X_ZERO = SCREEN_WIDTH / 2;
const int Y_ZERO = SCREEN_HEIGHT / 2;

const int a = -1, b = 2, c = 3;

const int x_lim = 10, y_lim = 10 * SCREEN_HEIGHT / SCREEN_WIDTH;

const int x_scale = SCREEN_WIDTH / (2 * x_lim); //50
const int y_scale = SCREEN_HEIGHT / (2 * y_lim); //40



double max(double a, double b)
{
	return (a > b) ? a : b;
}

float clamp(float n, float max, float min)
{
	if (n > max)
	{
		return max;
	}

	else if (n < min)
	{
		return min;
	}

	else
	{
		return n;
	}
}

void DrawYAxis()
{
	const int arrow_len = 5;
	const int arrow_tang = 2;

	DrawLine(0, -SCREEN_HEIGHT, 0, SCREEN_HEIGHT, BLACK);

	DrawLine(0, -SCREEN_HEIGHT / 2 - 1, 0 - arrow_len, -SCREEN_HEIGHT / 2 + arrow_tang * arrow_len - 1, BLACK); //Левая сторона стрелки
	DrawLine(0, -SCREEN_HEIGHT / 2 , 0 + arrow_len, -SCREEN_HEIGHT / 2 + arrow_tang * arrow_len, BLACK); // Правая сторона стрелки

	DrawText("y", 10, -SCREEN_HEIGHT / 2, 20, BLACK);


	char digit[5] = "";

	for (int y = -100; y < 100; y++)
	{
		sprintf(digit, "%d", -y);

		if (y != 0)
		{
			DrawText(digit, 0, y * y_scale, 10, BLACK);
		}
	}
}

void DrawXAxis()
{
	const int arrow_len = 5;
	const int arrow_tang = 2;

	DrawLine(-SCREEN_WIDTH, 0, SCREEN_WIDTH, 0, BLACK); 

	DrawLine(SCREEN_WIDTH / 2, 0 - 1, SCREEN_WIDTH / 2 - arrow_tang * arrow_len - 1, 0 + arrow_len, BLACK); //Верхняя сторона стрелки
	DrawLine(SCREEN_WIDTH / 2, 0, SCREEN_WIDTH / 2 - arrow_tang * arrow_len, 0 - arrow_len, BLACK); //Нижняя сторона стрелки

	DrawText("x", SCREEN_WIDTH / 2 - 20, 10 , 25, BLACK);

	char digit[5] = "";

	for (int x = -100; x < 100; x++)
	{
		sprintf(digit, "%d", x);

		if (x != 0)
		{
			DrawText(digit, x * x_scale, 0, 10, BLACK);
		}
	}
}

double f(double x, double a, double b, double c)
{
	return (a * x * x + b * x + c);
}

int main()
{
	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "test window for fun");

	Camera2D camera = {0};

	camera.target = (Vector2) {0.0f, 0.0f};

	camera.offset = (Vector2) {SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f};

	camera.rotation = 0.0f;
    camera.zoom = 1.0f;

	SetTargetFPS(60);

	while (!WindowShouldClose())
	{

		// double wheel = GetMouseWheelMove();

		// if (wheel != 0)
		// {
        // 	camera.zoom = Clamp(expf(logf(camera.zoom)+scale), 0.125f, 64.0f);

		// }

		if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
		{
			Vector2 zero_pos = Vector2Subtract(camera.offset, camera.target);

			camera.target = Vector2Subtract(GetMousePosition(), zero_pos);

			camera.offset = GetMousePosition();
		}

		BeginDrawing(); //Начало рисование

			ClearBackground(RAYWHITE);
 
				BeginMode2D(camera);

					rlPushMatrix(); //Установка нужной позиции композиции, чтобы сетка нормально выглядела

						rlScalef(1.0f, -1.0f, 1.0f);

						rlTranslatef(0, 25 * SCREEN_HEIGHT, 0);

						rlRotatef(90, 1.0f, 0.0f, 0.0f);

						DrawGrid(100 * SCREEN_WIDTH / x_scale, (int) max(x_scale, y_scale));

					rlPopMatrix();



					DrawYAxis();
					DrawXAxis();

					DrawText("0", -15, 0, 20, BLACK);

					double x = 0,  y = 0;

					double x_old = -x_lim, y_old = -f(x_old, a, b, c);
 
					for (x = - x_lim; x < x_lim; x += 0.0625f)
					{	


						y = -f(x, a, b, c);

						DrawLine(x_old * x_scale, y_old * y_scale, x * x_scale, y * y_scale, RED);

						x_old = x;
						y_old = y;

						//printf("mouse_x: %d, mouse_y: %d\n", GetMouseX(), GetMouseY());

						//DrawRectangle(x * x_scale - 2.5f, y * y_scale - 2.5f, 5, 5, RED);

						//printf("x * x_scale: %g, y * y_scale: %g\n", x*x_scale, y*y_scale);

						//Sleep(50);	
					}

				EndMode2D();					




		EndDrawing();
	}

	CloseWindow();

	return 0;

}