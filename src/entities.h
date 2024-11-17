#include <stdio.h>
#include <stdlib.h>

typedef enum {
	empty,
	red,
	blue,
} Colour;

typedef struct {
	int x;
	int y;
	Colour colour;
	int checked;
} Location;






