# Copyright 2018 Venice Unleashed - Reality mod devs. - Snaiperskaya.
# All rights reserved.
# Use of this source code is governed by a BSD-style license
# that can be found in the LICENSE file at the root of the
# Mumble source tree or at <https://www.mumble.info/LICENSE>.

include(../plugins.pri)

TARGET = vu
SOURCES = vu.cpp
LIBS += -luser32 -lWs2_32 -lMswsock -lAdvapi32
