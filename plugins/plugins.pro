# Copyright 2005-2018 The Mumble Developers. All rights reserved.
# Use of this source code is governed by a BSD-style license
# that can be found in the LICENSE file at the root of the
# Mumble source tree or at <https://www.mumble.info/LICENSE>.

include(../qmake/compiler.pri)

TEMPLATE = subdirs

CONFIG += debug_and_release
SUBDIRS = link \
    vu

win32 {
  SUBDIRS += bf3 vu

  equals(MUMBLE_ARCH, x86_64) {
    #SUBDIRS += bf1 bf4 ffxiv_x64 gtav wow_x64
  }
}

linux {
  SUBDIRS += l4d2 rl
}
