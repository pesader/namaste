/* namaste-window.c
 *
 * Copyright 2022 Pedro Sader Azevedo
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "config.h"
#include "webkit2/webkit2.h"

#include "namaste-window.h"

struct _NamasteWindow
{
  AdwApplicationWindow  parent_instance;

  /* Template widgets */
  GtkHeaderBar        *header_bar;
  WebKitWebView       *webview;
};

G_DEFINE_FINAL_TYPE (NamasteWindow, namaste_window, ADW_TYPE_APPLICATION_WINDOW)

static void
url_entry_activated (GtkEntry *entry,
                     NamasteWindow *self)
{
	const char *url = NULL;
	GUri *guri;

	url = gtk_editable_get_text(GTK_EDITABLE (entry));
	guri = g_uri_parse(url, G_URI_FLAGS_NONE, NULL);

	if (guri == NULL || ! g_str_has_prefix(url, "https://") || g_str_has_prefix(url, "http://"))
		{
			g_warning ("Isso não é uma URL!");
			return;
		}
	webkit_web_view_load_uri(self->webview, url);
}

static void
namaste_window_class_init (NamasteWindowClass *klass)
{
  GtkWidgetClass *widget_class = GTK_WIDGET_CLASS (klass);

  g_type_ensure(WEBKIT_TYPE_WEB_VIEW);

  gtk_widget_class_set_template_from_resource (widget_class, "/dev/lkcamp/Namaste/namaste-window.ui");
  gtk_widget_class_bind_template_child (widget_class, NamasteWindow, header_bar);
  gtk_widget_class_bind_template_child (widget_class, NamasteWindow, webview);
	gtk_widget_class_bind_template_callback (widget_class, url_entry_activated);
}

static void
namaste_window_init (NamasteWindow *self)
{
  gtk_widget_init_template (GTK_WIDGET (self));
	webkit_web_view_load_uri(self->webview, "https://lkcamp.dev");
}