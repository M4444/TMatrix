/*
 * Copyright (C) 2018-2019 Miloš Stojanović
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */

#include "TerminalChar.h"

template <>
const char *BaseTerminalChar<true>::GLOWING_COLOR_ESC_SEQ {Color::GetColor("white").Shade1};
template <>
const char *BaseTerminalChar<true>::NORMAL_COLOR_ESC_SEQ {nullptr};
template <>
const char *BaseTerminalChar<false>::GLOWING_COLOR_ESC_SEQ {Color::GetColor("white").Foreground};
template <>
const char *BaseTerminalChar<false>::NORMAL_COLOR_ESC_SEQ {nullptr};

const char *TerminalChar<true>::NORMAL_COLOR_ESC_SEQ_2 {nullptr};
const char *TerminalChar<true>::NORMAL_COLOR_ESC_SEQ_3 {nullptr};
const char *TerminalChar<true>::NORMAL_COLOR_ESC_SEQ_4 {nullptr};
