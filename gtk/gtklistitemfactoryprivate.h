/*
 * Copyright © 2018 Benjamin Otte
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library. If not, see <http://www.gnu.org/licenses/>.
 *
 * Authors: Benjamin Otte <otte@gnome.org>
 */


#ifndef __GTK_LIST_ITEM_FACTORY_H__
#define __GTK_LIST_ITEM_FACTORY_H__

#include <gtk/gtklistitem.h>
#include <gtk/gtklistview.h>

G_BEGIN_DECLS

#define GTK_TYPE_LIST_ITEM_FACTORY         (gtk_list_item_factory_get_type ())
#define GTK_LIST_ITEM_FACTORY(o)           (G_TYPE_CHECK_INSTANCE_CAST ((o), GTK_TYPE_LIST_ITEM_FACTORY, GtkListItemFactory))
#define GTK_LIST_ITEM_FACTORY_CLASS(k)     (G_TYPE_CHECK_CLASS_CAST ((k), GTK_TYPE_LIST_ITEM_FACTORY, GtkListItemFactoryClass))
#define GTK_IS_LIST_ITEM_FACTORY(o)        (G_TYPE_CHECK_INSTANCE_TYPE ((o), GTK_TYPE_LIST_ITEM_FACTORY))
#define GTK_IS_LIST_ITEM_FACTORY_CLASS(k)  (G_TYPE_CHECK_CLASS_TYPE ((k), GTK_TYPE_LIST_ITEM_FACTORY))
#define GTK_LIST_ITEM_FACTORY_GET_CLASS(o) (G_TYPE_INSTANCE_GET_CLASS ((o), GTK_TYPE_LIST_ITEM_FACTORY, GtkListItemFactoryClass))

typedef struct _GtkListItemFactory GtkListItemFactory;
typedef struct _GtkListItemFactoryClass GtkListItemFactoryClass;

struct _GtkListItemFactory
{
  GObject parent_instance;
};

struct _GtkListItemFactoryClass
{
  GObjectClass parent_class;

  /* setup @list_item so it can be bound */
  void                  (* setup)                               (GtkListItemFactory     *self,
                                                                 GtkListItem            *list_item);
  /* undo the effects of GtkListItemFactoryClass::setup() */
  void                  (* teardown)                            (GtkListItemFactory     *self,
                                                                 GtkListItem            *list_item);

  /* bind @list_item to the given @item, which is in @position and @selected state */
  void                  (* bind)                                (GtkListItemFactory     *self,
                                                                 GtkListItem            *list_item,
                                                                 guint                   position,
                                                                 gpointer                item,
                                                                 gboolean                selected);
  /* unbind the current item and bind a new one */
  void                  (* rebind)                              (GtkListItemFactory     *self,
                                                                 GtkListItem            *list_item,
                                                                 guint                   position,
                                                                 gpointer                item,
                                                                 gboolean                selected);
  /* like GtkListItemFactoryClass::rebind(), but the item didn't change */
  void                  (* update)                              (GtkListItemFactory     *self,
                                                                 GtkListItem            *list_item,
                                                                 guint                   position,
                                                                 gboolean                selected);
  /* undo the effects of GtkListItemFactoryClass::bind() */
  void                  (* unbind)                              (GtkListItemFactory     *self,
                                                                 GtkListItem            *list_item);
};

GType                   gtk_list_item_factory_get_type          (void) G_GNUC_CONST;

void                    gtk_list_item_factory_setup             (GtkListItemFactory     *self,
                                                                 GtkListItem            *list_item);
void                    gtk_list_item_factory_teardown          (GtkListItemFactory     *self,
                                                                 GtkListItem            *list_item);

void                    gtk_list_item_factory_bind              (GtkListItemFactory     *self,
                                                                 GtkListItem            *list_item,
                                                                 guint                   position,
                                                                 gpointer                item,
                                                                 gboolean                selected);
void                    gtk_list_item_factory_rebind            (GtkListItemFactory     *self,
                                                                 GtkListItem            *list_item,
                                                                 guint                   position,
                                                                 gpointer                item,
                                                                 gboolean                selected);
void                    gtk_list_item_factory_update            (GtkListItemFactory     *self,
                                                                 GtkListItem            *list_item,
                                                                 guint                   position,
                                                                 gboolean                selected);
void                    gtk_list_item_factory_unbind            (GtkListItemFactory     *self,
                                                                 GtkListItem            *list_item);


G_END_DECLS

#endif /* __GTK_LIST_ITEM_FACTORY_H__ */