# Copyright (C) 2018-2020 Miloš Stojanović
#
# SPDX-License-Identifier: GPL-2.0-only
#
# To use this completion script:
#    1) Copy this file to ${HOME}:
#        cp tmatrix-completion.tcsh ~/.tmatrix-completion.tcsh
#    2) Add the following line to your .tcshrc/.cshrc:
#        source ~/.tmatrix-completion.tcsh

set tmatrix_short_options = (\
	-s \
	-f \
	-G \
	-l \
	-r \
	-C \
	-c \
	-t \
)

set tmatrix_long_options = (\
	--mode \
	--steps-per-sec \
	--fall-speed \
	--start-gap \
	--gap \
	--fade \
	--no-fade \
	--color \
	--background \
	--title \
)

set tmatrix_modes = ( default dense )

set tmatrix_colors = (\
	default \
	white \
	gray \
	black \
	red \
	green \
	yellow \
	blue \
	magenta \
	cyan \
)

complete tmatrix \
	'n/-c/$tmatrix_colors/' \
	'n/-C/$tmatrix_colors/' \
	'c/--color=/$tmatrix_colors/' \
	'c/--background=/$tmatrix_colors/' \
	'c/--mode=/$tmatrix_modes/' \
	'n/--help/n/' \
	'n/--version/n/' \
	'n/--fade/n/' \
	'n/--no-fade/n/' \
	'C/--h/(--help)/' \
	'C/--v/(--version)/' \
	'C/--f/(--fade)/' \
	'C/--n/(--no-fade)/' \
	'C/--/$tmatrix_long_options/=/' \
	'C/-/$tmatrix_short_options/' \
	'p/*/n/' # don't complete file names and alike
