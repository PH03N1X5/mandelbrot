#include<math.h>
#include<complex.h>

#include"raylib.h"

const Color BACKGROUND = {0x21, 0x21, 0x21, 0xff};

int main()
{
	const int font_size = 20;

	int help = 1;
	char *help_msg[] = {
		"HJKL/Arrow keys - move",     
		"= - zoom in",            
		"- - zoom out",           
		"R - reset",         
		"I - reduce iterations",  
		"O - increase iterations",
		"G - Hide help window",   
		"Q - QUIT",               
	};
	int help_msg_count = sizeof(help_msg)/sizeof(help_msg[0]);

	int help_max = 0;
	for (int k = 0; k < help_msg_count; ++k)
	{
		int c = MeasureText(help_msg[k], font_size);
		if (help_max < c) help_max = c;
	}

	const int WIDTH = 900;
	const int HEIGHT = 600;
	const float MAGIC = 300.0;

	InitWindow(WIDTH, HEIGHT, "Mandelbrot Set");
	Shader shader = LoadShader(0, "mandelbrot.glsl");
	RenderTexture2D target = LoadRenderTexture(GetScreenWidth(), GetScreenHeight());

	// uniform
	Vector2 translate= {-5/4.0, -1/2.0}; 
	Vector2 scale = {WIDTH/MAGIC, HEIGHT/MAGIC};
	int iterations = 128;

	int id_t  = GetShaderLocation(shader, "t");
	int id_s  = GetShaderLocation(shader, "s");
	int id_it = GetShaderLocation(shader, "iterations");

	SetShaderValue(shader, id_t,  &translate,  SHADER_UNIFORM_VEC2);
	SetShaderValue(shader, id_s,  &scale,      SHADER_UNIFORM_VEC2);
	SetShaderValue(shader, id_it, &iterations, SHADER_UNIFORM_INT);

	SetTargetFPS(60);

	while (!WindowShouldClose()) 
	{
		// reset
		if (IsKeyDown(KEY_R))       iterations = 64,
					    translate.x = -1/2.0, translate.y = -1/2.0,
					    scale.x = WIDTH/MAGIC, scale.y = HEIGHT/MAGIC;

		if (IsKeyDown(KEY_H))       translate.x -= (scale.x+scale.y)/MAGIC; 
		if (IsKeyDown(KEY_LEFT))    translate.x -= (scale.x+scale.y)/MAGIC; 
		if (IsKeyDown(KEY_J))       translate.y += (scale.x+scale.y)/MAGIC; 
		if (IsKeyDown(KEY_DOWN))    translate.y += (scale.x+scale.y)/MAGIC; 
		if (IsKeyDown(KEY_K))       translate.y -= (scale.x+scale.y)/MAGIC; 
		if (IsKeyDown(KEY_UP))      translate.y -= (scale.x+scale.y)/MAGIC; 
		if (IsKeyDown(KEY_L))       translate.x += (scale.x+scale.y)/MAGIC; 
		if (IsKeyDown(KEY_RIGHT))   translate.x += (scale.x+scale.y)/MAGIC; 
		const double zoom = 1.05;
		if (IsKeyDown(KEY_MINUS))   scale.x *= zoom, scale.y *= zoom; 
		if (IsKeyDown(KEY_EQUAL))   scale.x /= zoom, scale.y /= zoom; 
		if (IsKeyDown(KEY_I))       iterations --; 
		if (IsKeyDown(KEY_O))       iterations ++; 
		if (IsKeyPressed(KEY_F1))   help ^= 1; 
		if (IsKeyPressed(KEY_G))    help ^= 1; 
		if (IsKeyDown(KEY_Q))       break; 

		SetShaderValue(shader, id_s,  &scale,      SHADER_UNIFORM_VEC2);
		SetShaderValue(shader, id_t,  &translate,  SHADER_UNIFORM_VEC2);
		SetShaderValue(shader, id_it, &iterations, SHADER_UNIFORM_INT);

		BeginTextureMode(target);
		ClearBackground(BACKGROUND);
		DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), BACKGROUND);
		EndTextureMode();

		BeginDrawing();
		ClearBackground(BACKGROUND);

		BeginShaderMode(shader);
		DrawTextureEx(target.texture, (Vector2){0, 0}, 0, 1, WHITE);
		EndShaderMode();

		if (help)
		{
			const int pad = 7;
			DrawRectangle(  pad,   pad, help_max + 4*pad, font_size * (help_msg_count) + 4*pad, GREEN);
			DrawRectangle(2*pad, 2*pad, help_max + 2*pad, font_size * (help_msg_count) + 2*pad, DARKGREEN);
			DrawCircle(0.5*WIDTH, 0.5*HEIGHT, 2, WHITE);
			int k = 0;
			for (int k = 0; k < help_msg_count; ++k)
				DrawText(help_msg[k], 3*pad, (k)*font_size + 3*pad, font_size, WHITE );   
		}
		EndDrawing();

	}
	UnloadRenderTexture(target);
	UnloadShader(shader);
	CloseWindow();

	return 0;
}
