#include<stdio.h>
#include<math.h>
#include<complex.h>

#include"raylib.h"

const Color BACKGROUND = {0x21, 0x21, 0x21, 0xff};

float clength(complex float z)
{
	return sqrt(creal(z)*creal(z) + cimag(z)*cimag(z));
}

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
		if (help_max < c) 
			help_max = c;
	}


	const int WIDTH = 900;
	const int HEIGHT = 600;
	const float MAGIC = 300.0;

	Vector2 translate= {-5.0/4, -1.0/2}; 
	Vector2 scale = {WIDTH/MAGIC, HEIGHT/MAGIC};
	int iterations = 32;

	InitWindow(WIDTH, HEIGHT, "Mandelbrot Set");
	RenderTexture2D target = LoadRenderTexture(GetScreenWidth(), GetScreenHeight());
	SetTargetFPS(60);

	while (!WindowShouldClose()) 
	{
		
		// reset
		if (IsKeyDown(KEY_R)) iterations = 32,
			translate.x = -1/2.0, translate.y = -1/2.0,
			scale.x = WIDTH/MAGIC, scale.y = HEIGHT/MAGIC;

		if (IsKeyDown(KEY_H))       translate.x -= (scale.x + scale.y)/MAGIC;
		if (IsKeyDown(KEY_LEFT))    translate.x -= (scale.x + scale.y)/MAGIC;
		if (IsKeyDown(KEY_J))       translate.y -= (scale.x + scale.y)/MAGIC;
		if (IsKeyDown(KEY_DOWN))    translate.y -= (scale.x + scale.y)/MAGIC;
		if (IsKeyDown(KEY_K))       translate.y += (scale.x + scale.y)/MAGIC;
		if (IsKeyDown(KEY_UP))      translate.y += (scale.x + scale.y)/MAGIC;
		if (IsKeyDown(KEY_L))       translate.x += (scale.x + scale.y)/MAGIC;
		if (IsKeyDown(KEY_RIGHT))   translate.x += (scale.x + scale.y)/MAGIC;
		const double zoom = 1.05;
		if (IsKeyDown(KEY_MINUS))   scale.x *= zoom, scale.y *= zoom; 
		if (IsKeyDown(KEY_EQUAL))   scale.x /= zoom, scale.y /= zoom;  
		if (IsKeyDown(KEY_I))       iterations --; 
		if (IsKeyDown(KEY_O))       iterations ++; 
		if (IsKeyPressed(KEY_F1))   help ^= 1; 
		if (IsKeyPressed(KEY_G))    help ^= 1; 
		if (IsKeyDown(KEY_Q))       break; 

		BeginTextureMode(target);
		for(int j = 0; j <= HEIGHT; j++)
			for(int i = 0; i <= WIDTH; i++)
			{
				Vector2 pixel = {i, j};
				complex float c = 
					(( (float)i/WIDTH  -1/2.0) * scale.x + 1/2.0 + translate.x ) + 
					(( (float)j/HEIGHT -1/2.0) * scale.y + 1/2.0 + translate.y )*I ;
				complex float z = 0;
				int iter;
				for(iter = 0; iter < iterations && creal(z) < 2 && cimag(z) < 2 ; ++iter)
					z = z*z + c;
				float x = iter + 1 - log(log(clength(z))/log(2.0));
				float norm = x/iterations;

				if (norm > 0.999) 
					DrawPixelV(pixel, BLACK);  
				else 
					DrawPixelV(pixel, ColorFromHSV(240.0 - norm*360.0, 1.0, 1.0));  

			}
		EndTextureMode();

		BeginDrawing();
		ClearBackground(BACKGROUND);
		DrawTextureEx(target.texture, (Vector2){0, 0}, 0, 1, WHITE);

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
	CloseWindow();

	return 0;
}
