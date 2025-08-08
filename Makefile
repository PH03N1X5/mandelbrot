all : mandelbrot_cli mandelbrot_gpu mandelbrot_cpu
mandelbrot_cli : mandelbrot_cli.c
	cc -o $@ $@.c -lm -lraylib
mandelbrot_gpu : mandelbrot_gpu.c
	cc -o $@ $@.c -lm -lraylib
mandelbrot_cpu : mandelbrot_cpu.c
	cc -o $@ $@.c -lm -lraylib
