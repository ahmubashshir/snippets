#!/bin/bash
if [[ $1 == "@single" ]]; then
	for ((i = 0; i < 100; i++)); do
		# XXX: Do your own job here.
		sleep $((i % 5))

		printf '\33[2K\r -> Completed tasks %d/%d' "$i" "100"
	done
	echo
elif [[ $1 == "@multi" ]]; then
	source "${0%/*}/../bash/multiprocessing"
else

	"${0%/*}/../.tools/bench" "$0 @multi" "$0 @single"
fi
