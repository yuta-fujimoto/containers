make -C bench

title=`./bench/ft | awk '{printf "%10s\n", $1}'`
ft=`./bench/ft | awk '{print $2}'`
std=`./bench/std | awk '{print $2}'`
ratio=`paste <(echo  "title") <(echo  "$ft") <(echo "$std") | awk '{print ($1/$2)}'`

echo "      NAME      ft       std     ft/std"
echo "--------------------------------------"
paste <(echo -e "$title") <(echo -e "$ft") <(echo -e "$std") <(echo -e "$ratio")

make fclean -C bench
