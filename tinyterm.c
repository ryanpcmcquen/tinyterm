/* tinyterm.c
 *
 * Copyright (C) 2009 Sebastian Linke
 *
 * This is free software; you can redistribute it and/or modify it under
 * the terms of the GNU Library General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */
 
#include <vte/vte.h>
#include "config.h"

/* Buffer size of terminal */
#define SCROLLBACK_LINES 10000

int
main (int argc, char *argv[])
{
    GtkWidget *window, *terminal, *scrollbar, *design;
    GError *icon_error;
    GdkPixbuf *icon;
    GdkGeometry geo_hints;

    /* Init gtk and all widgets */
    gtk_init (&argc, &argv);
    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    terminal = vte_terminal_new ();
    scrollbar = gtk_vscrollbar_new (VTE_TERMINAL (terminal)->adjustment);
    design = gtk_hbox_new (FALSE, 0);

    /* Set window icon */
    icon_error = NULL;
    icon = gdk_pixbuf_new_from_file (TINYTERM_ICON_PATH, &icon_error);
    if (!icon) {
        g_warning ("%s\n", icon_error->message);
        g_error_free (icon_error);
    }
    gtk_window_set_icon (GTK_WINDOW (window), icon);

    /* Set window title */
    gtk_window_set_title (GTK_WINDOW (window), "TinyTerm");

    /* Set scrollback lines */
    vte_terminal_set_scrollback_lines (VTE_TERMINAL (terminal), SCROLLBACK_LINES);

    /* Apply geometry hints to handle terminal resizing */
    geo_hints.base_width = VTE_TERMINAL (terminal)->char_width;
    geo_hints.base_height = VTE_TERMINAL (terminal)->char_height;
    geo_hints.min_width = VTE_TERMINAL (terminal)->char_width;
    geo_hints.min_height = VTE_TERMINAL (terminal)->char_height;
    geo_hints.width_inc = VTE_TERMINAL (terminal)->char_width;
    geo_hints.height_inc = VTE_TERMINAL (terminal)->char_height;
    gtk_window_set_geometry_hints (GTK_WINDOW (window), terminal, &geo_hints,
                                   GDK_HINT_RESIZE_INC | GDK_HINT_MIN_SIZE | GDK_HINT_BASE_SIZE);

    /* Open a shell */
    vte_terminal_fork_command (VTE_TERMINAL (terminal),
                               NULL, /* binary to run (NULL=user's shell) */
                               NULL, /* arguments */
                               NULL, /* environment */
                               NULL, /* dir to start (NULL=CWD) */
                               TRUE, /* log session to lastlog */
                               TRUE, /* log session to utmp/utmpx log */
                               TRUE);/* log session to wtmp/wtmpx log */

    /* Set signals when quitting */
    g_signal_connect (window, "delete-event", gtk_main_quit, NULL);
    g_signal_connect (terminal, "child-exited", gtk_main_quit, NULL);

    /* Put all widgets together and show the result */
    gtk_box_pack_start (GTK_BOX (design), terminal, TRUE, TRUE, 0);
    gtk_box_pack_start (GTK_BOX (design), scrollbar, FALSE, FALSE, 0);
    gtk_container_add (GTK_CONTAINER (window), design);
    gtk_widget_show_all (window);
    gtk_main ();

    return 0;
}
