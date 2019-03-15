#include <gtk/gtk.h>

static void print_hello(void) {
	g_print("Hello, world!\n");
}

static void print_question(void) {
	g_print("How are you?\n");
}

static void print_goodbye(void) {
	g_print("Goodbye!\n");
}

static void activate(GtkApplication *app) {
	GtkWidget *window;
	GtkWidget *grid;
	GtkWidget *button;

	/* create a new window and set its title */
	window = gtk_application_window_new(app);
	gtk_window_set_title(GTK_WINDOW(window), "Window");
	gtk_container_set_border_width(GTK_CONTAINER(window), 10);
	gtk_window_fullscreen(GTK_WINDOW(window));

	/*gtk_window_set_default_size(GTK_WINDOW(window), 200, 200);*/
	
	/* Here we construct the container that is going to pack our buttons */
	grid = gtk_grid_new();

	/* Pack the container in the window */
	gtk_container_add(GTK_CONTAINER(window), grid);

	button = gtk_button_new_with_label("Button 1");
	g_signal_connect(button, "clicked", G_CALLBACK(print_hello), NULL);

	/* Place the first button in the grid cell (0, 0), and make it fill just 1
	 * cell horizontally and vertically (i.e. no spanning) */
	gtk_grid_attach(GTK_GRID(grid), button, 0, 0, 1, 1);

	button = gtk_button_new_with_label("Button 2");
	g_signal_connect(button, "clicked", G_CALLBACK(print_question), NULL);

	/* Place the second button in the grid cell (1, 0), and make it fill just 1
	 * cell horizontally and vertically (i.e. no spanning) */
	gtk_grid_attach(GTK_GRID(grid), button, 1, 0, 1, 1);

	button = gtk_button_new_with_label("Quit");
	g_signal_connect(button, "clicked", G_CALLBACK(print_goodbye), NULL);
	g_signal_connect_swapped(button, "clicked", G_CALLBACK(gtk_widget_destroy),
			window);

	/* Place the quit button in the grid cell (0, 1), and make it span 2
	 * columns */
	gtk_grid_attach(GTK_GRID(grid), button, 0, 1, 2, 1);

	/* Now that we are done packing our widgets, we show them all in one go by
	 * calling gtk_widget_show_all() on the window. This call recursively calls
	 * gtk_widget_show() on all widgets that are contained in the window,
	 * directly or indirectly */
	gtk_widget_show_all(window);
}

int main(int argc, char *argv[]) {
	GtkApplication *app;
	int status;

	app = gtk_application_new("org.gtk.example", G_APPLICATION_FLAGS_NONE);
	g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
	status = g_application_run(G_APPLICATION(app), argc, argv);
	g_object_unref(app);

	return status;
}
