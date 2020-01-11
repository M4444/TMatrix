/*
 * Copyright (C) 2018-2019 Miloš Stojanović
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */

#include "TerminalChar.h"

const char *TerminalChar::GLOWING_COLOR_ESC_SEQ {Color::GetColor("white").Foreground};
const char *TerminalChar::NORMAL_COLOR_ESC_SEQ {nullptr};
