#include <cairo.h>

int
main (int argc, char *argv[])
{
	cairo_surface_t *surface;
	cairo_t *cr;
	cairo_text_extents_t te;

	/* Prepare drawing area */
	surface = cairo_image_surface_create (CAIRO_FORMAT_ARGB32, 120, 120);
	cr = cairo_create (surface);
	/* Examples are in 1.0 x 1.0 coordinate space */
	cairo_scale (cr, 120, 120);

	/* Drawing code goes here */
	cairo_set_source_rgb (cr, 0.0, 0.0, 0.0);
	cairo_select_font_face (cr, "Georgia",
			CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_BOLD);
	cairo_set_font_size (cr, 1.2);
	cairo_text_extents (cr, "a", &te);
	cairo_move_to (cr, 0.5 - te.width / 2 - te.x_bearing,
			0.5 - te.height / 2 - te.y_bearing);
	cairo_show_text (cr, "a");

	/* Write output and clean up */
	cairo_surface_write_to_png (surface, "showtext.png");
	cairo_destroy (cr);
	cairo_surface_destroy (surface);

	return 0;
}
