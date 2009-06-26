/*
 * Copyright (C) 2009 Rodney Cryderman <rcryderman@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Library General Public License version 
 * 2 or later as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 *
 */

/* awn-overlay-throbber.h */

#ifndef _AWN_OVERLAY_THROBBER
#define _AWN_OVERLAY_THROBBER

#include <gtk/gtk.h>
#include <glib-object.h>
#include "awn-overlay.h"

G_BEGIN_DECLS

#define AWN_TYPE_OVERLAY_THROBBER awn_overlay_throbber_get_type()

#define AWN_OVERLAY_THROBBER(obj) \
  (G_TYPE_CHECK_INSTANCE_CAST ((obj), AWN_TYPE_OVERLAY_THROBBER, AwnOverlayThrobber))

#define AWN_OVERLAY_THROBBER_CLASS(klass) \
  (G_TYPE_CHECK_CLASS_CAST ((klass), AWN_TYPE_OVERLAY_THROBBER, AwnOverlayThrobberClass))

#define AWN_IS_OVERLAY_THROBBER(obj) \
  (G_TYPE_CHECK_INSTANCE_TYPE ((obj), AWN_TYPE_OVERLAY_THROBBER))

#define AWN_IS_OVERLAY_THROBBER_CLASS(klass) \
  (G_TYPE_CHECK_CLASS_TYPE ((klass), AWN_TYPE_OVERLAY_THROBBER))

#define AWN_OVERLAY_THROBBER_GET_CLASS(obj) \
  (G_TYPE_INSTANCE_GET_CLASS ((obj), AWN_TYPE_OVERLAY_THROBBER, AwnOverlayThrobberClass))

typedef struct {
  AwnOverlay parent;
} AwnOverlayThrobber;

typedef struct {
  AwnOverlayClass parent_class;
} AwnOverlayThrobberClass;

GType awn_overlay_throbber_get_type (void);

GtkWidget* awn_overlay_throbber_new (GtkWidget *icon);

G_END_DECLS

#endif /* _AWN_OVERLAY_THROBBER */
