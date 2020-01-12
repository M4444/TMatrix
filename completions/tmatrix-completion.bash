# Copyright (C) 2018-2020 Miloš Stojanović
#
# SPDX-License-Identifier: GPL-2.0-only

_tmatrix() {
	local cur prev split
	_init_completion -s || return

	local colors=(default white gray black red green yellow blue magenta cyan)

	case $prev in
		--help|--version|--fade|--no-fade)
			return
			;;
		--background|-c|--color|-C)
			COMPREPLY=( $(compgen -W '${colors[*]}' -- "${cur}") )
			return
			;;
		--mode)
			COMPREPLY=( $(compgen -W 'default dense' -- "${cur}") )
			return
			;;
	esac

	$split && return

	if [[ $cur == -* ]]; then
		COMPREPLY=( $(compgen -W '$(_parse_help "$1")' -- "$cur") )
		COMPREPLY+=( $(compgen -W '-s -f -G -g -C -c -t' -- "$cur") )
		[[ "${COMPREPLY[0]}" == *= ]] && compopt -o nospace
		return
	fi
} && complete -F _tmatrix tmatrix
