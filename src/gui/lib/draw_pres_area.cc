#include <gtk/gtk.h>
#include <cmath>
#include "draw_pres_area.h"

bool draw_pres_area::draw(GtkWidget *widget, cairo_t *cr, gpointer data) {
    // constants
    const int width = 250;
    const int height = 150;
    const double inset = 3.5;
    const int radius = 100;

    // properties
    cairo_translate(cr, width / 2, height / 1.2);
    cairo_save(cr);

    // arc
    cairo_restore(cr);
    cairo_set_source_rgb(cr, 0.8, 0.8, 0.8);
    cairo_arc(cr, 0, 0, radius, M_PI, 2 * M_PI);
    cairo_save(cr);
    cairo_set_source_rgb(cr, 0.8, 0.8, 0.8);
    cairo_fill_preserve(cr);
    cairo_restore(cr);
    cairo_stroke_preserve(cr);
    cairo_clip(cr);

    // ticks
    for (int i = 6; i <= 12; i++) {
        cairo_set_source_rgb(cr, 0.0, 0.0, 0.0); //black
        cairo_save(cr);
        cairo_set_line_cap(cr, CAIRO_LINE_CAP_ROUND);

        cairo_move_to(cr, 
            (radius - inset) * cos(i * M_PI / 6),
            (radius - inset) * sin(i * M_PI / 6)
        );

        cairo_line_to(cr, 
            radius * cos(i * M_PI / 6),
            radius * sin(i * M_PI / 6)
        );

        cairo_stroke(cr);
        cairo_restore(cr);
    }

    // needle
    time_t rawtime;
    time(&rawtime);
    struct tm * timeinfo = localtime (&rawtime);

    double seconds= timeinfo->tm_sec * M_PI / 30;
    // double data = acc.get_data() * M_PI / 30;

    cairo_save(cr);
    cairo_set_line_cap(cr, CAIRO_LINE_CAP_ROUND);
    cairo_save(cr);
    cairo_set_source_rgb(cr, 0.0, 0.5, 1.0); // lightblue
    cairo_move_to(cr, 0, 0);
    // cr->line_to(sin(0) * (radius * 0.95), -cos(0) * (radius * 0.95));
    cairo_line_to(cr,
        sin(seconds) * (radius * 0.95),
        -cos(seconds) * (radius * 0.95)
    );
    cairo_stroke(cr);
    cairo_restore(cr);

    // dot
    cairo_arc(cr, 0, 0, width*.015, 0, 2 * M_PI);
    cairo_set_source_rgb(cr, 0.0, 0.5, 1.0); // lightblue
    cairo_fill(cr);
    cairo_restore(cr);

    return false;
}