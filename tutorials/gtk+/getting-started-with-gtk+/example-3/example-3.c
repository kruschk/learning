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

int main(int argc, char *argv[]) {
	GtkBuilder *builder;
	GObject *window;
	GObject *button;
	GError *error = NULL;

	gtk_init(&argc, &argv);

	/* Construct a GtkBuilder instance and load our UI description */
	builder = gtk_builder_new();
	if (gtk_builder_add_from_file(builder, "builder.ui", &error) == 0) {
		g_printerr("Error loading file: %s\n", error->message);
		g_clear_error(&error);
		return 1;
	}

	/* Connect signal handlers to the constructed widgets */
	window = gtk_builder_get_object(builder, "window");
	g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

	button = gtk_builder_get_object(builder, "button1");
	g_signal_connect(button, "clicked", G_CALLBACK(print_hello), NULL);

	button = gtk_builder_get_object(builder, "button2");
	g_signal_connect(button, "clicked", G_CALLBACK(print_question), NULL);

	button = gtk_builder_get_object(builder, "quit");
	g_signal_connect(button, "clicked", G_CALLBACK(print_goodbye), NULL);
	g_signal_connect(button, "clicked", G_CALLBACK(gtk_main_quit), NULL);

	gtk_main();

	return 0;
}
