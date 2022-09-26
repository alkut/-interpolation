#include <stdio.h>
#include "interpolation.h"

int main()
{
	interpolation_ctx ctx;

	ctx = interpolation_create(2,
				   1000, 5, -5, 5);

	printf("val: %lf\n", interpolation_calculate(ctx, 1.5));

	interpolation_destroy(ctx);

	return 0;
}
