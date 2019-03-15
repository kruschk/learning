#include <cairo.h>

int main (int argc, char *argv[]) {
	cairo_surface_t *surface;
	cairo_t *cr;

	surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, 120, 120);
	cr = cairo_create(surface);
	/* Examples are in 1.0 x 1.0 coordinate space */
	cairo_scale(cr, 120, 120);

	/* Drawing code goes here */
	cairo_set_source_rgb(cr, 0, 0, 0);
	cairo_rectangle(cr, 0.25, 0.25, 0.5, 0.5);
	cairo_fill(cr);

	/* Write output and clean up */
	cairo_surface_write_to_png(surface, "fill.png");
	cairo_destroy(cr);
	cairo_surface_destroy(surface);

	return 0;
}

