#/bin/bash

# https://wiki.archlinux.org/index.php/Bash/Prompt_customization

# 00=none 01=bold 04=underscore 05=blink 07=reverse 08=concealed (attribute codes)
# 0=black 1=red 2=green 3=yellow 4=blue 5=magenta 6=cyan 7=white
# +30 for foreground/text color
# +40 for background color

# echo -e "\033[47;30m ===> \033[0m"
# echo -e "\e[47;30m ===> \e[0m"

for STYLE in 0 1 2 3 4 5 6 7; do
	for FG in 30 31 32 33 34 35 36 37; do
		for BG in 40 41 42 43 44 45 46 47; do
			CTRL="\033[${STYLE};${FG};${BG}m"
			echo -en "${CTRL}"
			echo -n "${STYLE};${FG};${BG}"
			echo -en "\033[0m"
		done
		echo
	done
	echo
done
# Reset
echo -e "\033[0m"
