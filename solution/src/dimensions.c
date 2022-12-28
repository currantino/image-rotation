#include "dimensions.h"

struct dimensions dimensions_reverse(const struct dimensions *dim)
{
	const struct dimensions reversed_dim = {.x = dim->y, .y = dim->x};
	return reversed_dim;
}
