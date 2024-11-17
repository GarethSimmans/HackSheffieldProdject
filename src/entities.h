#include <stdio.h>
#include <stdlib.h>

typedef enum {
	EMPTY,
	TRED,
	TBLUE,
} Colour;

typedef struct {
	int x;
	int y;
	Colour colour;
} Location;

