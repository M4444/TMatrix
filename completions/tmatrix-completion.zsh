#compdef tmatrix

# Copyright (C) 2018-2020 Miloš Stojanović
#
# SPDX-License-Identifier: GPL-2.0-only

local colors=(default white gray black red green yellow blue magenta cyan)

_arguments \
	--mode=-"[Set the mode of the rain]:"\
"mode:(default dense)" \
	{-C+,--color=-}"[Set the color of the characters]:"\
"color:(${colors[*]})" \
	{-c+,--background=-}"[Set the color of the background]:"\
"color:(${colors[*]})" \
	--
