/*
 * Neuromapp - queue.cpp, Copyright (c), 2015,
 * Kai Langen - Swiss Federal Institute of technology in Lausanne,
 * kai.langen@epfl.ch,
 * All rights reserved.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 3.0 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library.
 */

/**
 * @file neuromapp/queueing/queue.cpp
 * \brief Contains Queue and Event class implementation
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <utility>

#include "queueing/queue.h"

namespace queueing {

void queue::insert(double tt, double d) {
    pq_que.push(event(d,tt));
}

bool queue::atomic_dq(double tt, event& q) {
    if(!pq_que.empty() && pq_que.top().t_ <= tt) {
        q = pq_que.top();
        pq_que.pop();
		return true;
	}
    return false;
}

}
