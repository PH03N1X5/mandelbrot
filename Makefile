all : mandelbrot_cli mandelbrot_gpu
mandelbrot_cli : mandelbrot_cli.c
	cc -o $@ $@.c -lm -lraylib
mandelbrot_gpu : mandelbrot_gpu.c
	cc -o $@ $@.c -lm -lraylib
