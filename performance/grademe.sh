make

title=`./ft | awk '{print $1}'`
ft=`./ft | awk '{print $2}'`
std=`./std | awk '{print $2}'`
ratio=`paste <(echo "$ft") <(echo "$std") | awk '{print ($1/$2)}'`

echo "NAME           ft       std     ft/std"
echo "--------------------------------------"
paste <(./ft) <(echo -e "$std") <(echo -e "$ratio")
