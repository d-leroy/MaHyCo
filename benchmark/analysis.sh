for dir in */
do
	f=$dir/output/listing/logs.0
	if [ -f "$f" ]; then
		str=$(cat $f | awk '/::applyEOS / {print "::applyEOS\t" $2}')
		trimmed=$(echo "${dir}" | sed 's:/*$::')
		echo "${trimmed}${str}"
	fi
done
