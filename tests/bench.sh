make -C bench

function compare() {
	echo -e "\n[                     $1                     ]\n"
	title=`./bench/ft_$1 | awk '{printf "%10s\n", $1}'`
	ft=`./bench/ft_$1 | awk '{print $2}'`
	std=`./bench/std_$1 | awk '{print $2}'`
	ratio=`paste  <(echo  "$ft") <(echo "$std") | awk '{print ($1/$2)}'`
	
	paste <(echo -e "$title") <(echo -e "$ft") <(echo -e "$std") <(echo -e "$ratio")
}

## TITLE

echo "      NAME      ft       std     ft/std"
echo "--------------------------------------------------"

## VECTOR
compare vector

## STACK
compare stack

## MAP
compare map

## SET
compare set

make fclean -C bench
