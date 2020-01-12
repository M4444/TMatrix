/*
 * Copyright (C) 2018-2019 Miloš Stojanović
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */

#include "TerminalChar.h"

const char *TerminalChar::GLOWING_COLOR_ESC_SEQ {Color::GetColor("white").Shade1};
const char *TerminalChar::NORMAL_COLOR_ESC_SEQ {nullptr};
const char *TerminalChar::NORMAL_COLOR_ESC_SEQ_2 {nullptr};
const char *TerminalChar::NORMAL_COLOR_ESC_SEQ_3 {nullptr};
const char *TerminalChar::NORMAL_COLOR_ESC_SEQ_4 {nullptr};
