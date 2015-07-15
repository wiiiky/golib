/*
 * Copyright (C) 2015  Wiky L
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with the package; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor Boston, MA 02110-1301,  USA
 */

#include "jobject.h"
#include "jatomic.h"
#include "jmem.h"


JObject *j_object_new_proxy(jpointer priv, JObjectDestroy _free)
{
    JObject *obj = j_malloc(sizeof(JObject));
    obj->ref = 1;
    obj->priv = priv;
    obj->free = _free;
    return obj;
}

void j_object_ref(JObject * obj)
{
    j_atomic_int_inc(&obj->ref);
}

void j_object_unref(JObject * obj)
{
    if (j_atomic_int_dec_and_test(&obj->ref)) {
        if (obj->free) {
            obj->free(obj->priv);
        }
        j_free(obj);
    }
}
