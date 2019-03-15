#include <gtk/gtk.h>

int main(int argc, char *argv[]) {
	GtkWidget *window;

	gtk_init(&argc, &argv); /* initialize gtk+ */

	window = gtk_window_new(GTK_WINDOW_TOPLEVEL); /* create top-level window */
	gtk_widget_show(window);                      /* show the window */

	g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

	gtk_main();

	return 0;
}
