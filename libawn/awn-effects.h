/*
 *  Copyright (C) 2007 Michal Hruby <michal.mhr@gmail.com>
 *  Copyright (C) 2008 Rodney Cryderman <rcryderman@gmail.com>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */

#ifndef _LIBAWN_AWN_EFFECTS_H
#define _LIBAWN_AWN_EFFECTS_H

#include <glib.h>
#include <glib-object.h>
#include <gtk/gtk.h>

#include "awn-defines.h"
#include "awn-config-client.h"

G_BEGIN_DECLS

typedef enum
{
  AWN_EFFECT_NONE = 0,
  AWN_EFFECT_OPENING = 1,
  AWN_EFFECT_CLOSING = 2,
  AWN_EFFECT_HOVER = 3,
  AWN_EFFECT_LAUNCHING = 4,
  AWN_EFFECT_ATTENTION = 5,
  AWN_EFFECT_DESATURATE
} AwnEffect;

typedef enum
{
  AWN_EFFECT_DIR_NONE,
  AWN_EFFECT_DIR_STOP,
  AWN_EFFECT_DIR_DOWN,
  AWN_EFFECT_DIR_UP,
  AWN_EFFECT_DIR_LEFT,
  AWN_EFFECT_DIR_RIGHT,
  AWN_EFFECT_SQUISH_DOWN,
  AWN_EFFECT_SQUISH_DOWN2,
  AWN_EFFECT_SQUISH_UP,
  AWN_EFFECT_SQUISH_UP2,
  AWN_EFFECT_TURN_1,
  AWN_EFFECT_TURN_2,
  AWN_EFFECT_TURN_3,
  AWN_EFFECT_TURN_4,
  AWN_EFFECT_SPOTLIGHT_ON,
  AWN_EFFECT_SPOTLIGHT_TREMBLE_UP,
  AWN_EFFECT_SPOTLIGHT_TREMBLE_DOWN,
  AWN_EFFECT_SPOTLIGHT_OFF
} AwnEffectSequence;

typedef void (*AwnEventNotify)(GtkWidget *);

//GObject stuff
#define AWN_TYPE_EFFECTS awn_effects_get_type()

#define AWN_EFFECTS(obj) \
  (G_TYPE_CHECK_INSTANCE_CAST ((obj), AWN_TYPE_EFFECTS, AwnEffects))

#define AWN_EFFECTS_CLASS(klass) \
  (G_TYPE_CHECK_CLASS_CAST ((klass), AWN_TYPE_EFFECTS, AwnEffectsClass))

#define AWN_IS_EFFECTS(obj) \
  (G_TYPE_CHECK_INSTANCE_TYPE ((obj), AWN_TYPE_EFFECTS))

#define AWN_IS_EFFECTS_CLASS(klass) \
  (G_TYPE_CHECK_CLASS_TYPE ((klass), AWN_TYPE_EFFECTS))

#define AWN_EFFECTS_GET_CLASS(obj) \
  (G_TYPE_INSTANCE_GET_CLASS ((obj), AWN_TYPE_EFFECTS, AwnEffectsClass))

/**
 * AwnEffects:
 *
 * Structure containing all necessary variables for effects state for
 * particular widget.
 */
typedef struct _AwnEffects AwnEffects;
typedef struct _AwnEffectsClass AwnEffectsClass;

typedef gboolean(* AwnEffectsOpfn )(AwnEffects * fx,
                                     GtkAllocation * alloc,
                                     gpointer user_data);

typedef struct
{
  AwnEffectsOpfn      fn;
  gpointer            data;
} AwnEffectsOp;

struct _AwnEffects
{
  GObject parent;

  AwnConfigClient *client;

  GtkWidget *self;
  GList *effect_queue;

  GSourceFunc sleeping_func;

  gint icon_width, icon_height;
  gint window_width, window_height;

  /* EFFECT VARIABLES */
  gboolean effect_lock;
  AwnEffect current_effect;
  AwnEffectSequence direction;
  gint count;

  gdouble side_offset;
  gdouble top_offset;
  gdouble curve_offset;

  gint delta_width;
  gint delta_height;

  GtkAllocation clip_region;

  gdouble rotate_degrees;
  gfloat alpha;
  gfloat spotlight_alpha;
  gfloat saturation;
  gfloat glow_amount;

  gint icon_depth;
  gint icon_depth_direction;

  /* State variables */
  gboolean hover;
  gboolean clip;
  gboolean flip;
  gboolean spotlight;

  /* Properties */
  gint orientation;
  guint set_effects;
  gint icon_offset;
  gint refl_offset;
  gfloat icon_alpha;
  gfloat refl_alpha;
  gboolean do_reflection;
  gboolean make_shadow;
  gboolean is_active;
  gchar *label;
  gint border_clip;
  /* properties end */

  guint timer_id;

  cairo_t * icon_ctx;
  cairo_t * reflect_ctx;

  AwnEffectsOp  *op_list;

  /* padding so we dont break ABI compability every time */
  void *pad1;
  void *pad2;
  void *pad3;
};

struct _AwnEffectsClass {
  GObjectClass parent_class;

  GPtrArray *animations;
};

GType awn_effects_get_type(void);

/**
 * awn_effects_new_for_widget:
 * @widget: Object which will be passed to all callback functions, this object
 * is also passed to gtk_widget_queue_draw() during the animation.
 *
 * Creates and initializes new #AwnEffects structure.
 */
AwnEffects* awn_effects_new_for_widget(GtkWidget * widget);

/**
 * awn_effects_start:
 * @fx: Pointer to #AwnEffects structure.
 * @effect: #AwnEffect to schedule.
 *
 * Start a single effect. The effect will loop until awn_effect_stop()
 * is called.
 */
void awn_effects_start(AwnEffects * fx, const AwnEffect effect);

/**
 * awn_effects_stop:
 * @fx: Pointer to #AwnEffects structure.
 * @effect: #AwnEffect to stop.
 *
 * Stop a single effect.
 */

void awn_effects_stop(AwnEffects * fx, const AwnEffect effect);

/**
 * awn_effects_start_ex:
 * @fx: Pointer to #AwnEffects structure.
 * @effect: Effect to schedule.
 * @start: Function which will be called when animation starts.
 * @stop: Function which will be called when animation finishes.
 * @max_loops: Number of maximum animation loops (0 for unlimited).
 *
 * Extended effect start, which provides callbacks for animation start, end and
 * possibility to specify maximum number of loops.
 */
void
awn_effects_start_ex(AwnEffects * fx, const AwnEffect effect,
                    AwnEventNotify start, AwnEventNotify stop,
                    gint max_loops);

void awn_effects_draw_background(AwnEffects *, cairo_t *) G_GNUC_DEPRECATED;
void awn_effects_draw_icons(AwnEffects *, cairo_t *, GdkPixbuf *, GdkPixbuf *) G_GNUC_DEPRECATED;
void awn_effects_draw_icons_cairo(AwnEffects * fx, cairo_t * cr, cairo_t * , cairo_t *) G_GNUC_DEPRECATED;
void awn_effects_draw_foreground(AwnEffects *, cairo_t *) G_GNUC_DEPRECATED;

void awn_effects_draw_set_window_size(AwnEffects *, const gint, const gint) G_GNUC_DEPRECATED;

void awn_effects_draw_set_icon_size(AwnEffects *, const gint, const gint, gboolean requestSize);

cairo_t *awn_effects_draw_cairo_create(AwnEffects *);
cairo_t *awn_effects_draw_get_window_context(AwnEffects *);
void awn_effects_draw_clear_window_context(AwnEffects *);
void awn_effects_draw_cairo_destroy(AwnEffects *);

void awn_effects_redraw(AwnEffects *);

// we no longer need this, there are properties instead
void awn_effects_reflection_off(AwnEffects * fx) G_GNUC_DEPRECATED;
void awn_effects_reflection_on(AwnEffects * fx) G_GNUC_DEPRECATED;
void awn_effects_set_reflection_visible(AwnEffects * fx, gboolean value) G_GNUC_DEPRECATED;
void awn_effects_set_offset_cut(AwnEffects * fx, gboolean cut) G_GNUC_DEPRECATED;

G_END_DECLS

//Move this somewhere else eventually
void awn_effects_main_effect_loop(AwnEffects * fx);

#endif
