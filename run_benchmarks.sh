#!/usr/bin/env bash

set -e

echo "=============================="
echo "   UM Benchmark Results"
echo "=============================="
echo

run_time() {
    name=$1
    cmd=$2

    echo "---- $name ----"
    
    # Run and capture time output
    result=$( (/usr/bin/time -p bash -c "$cmd") 2>&1 >/dev/null )

    # Extract values
    real=$(echo "$result" | grep "^real" | awk '{print $2}')
    user=$(echo "$result" | grep "^user" | awk '{print $2}')
    sys=$(echo "$result" | grep "^sys" | awk '{print $2}')

    printf "real: %-8s user: %-8s sys: %-8s\n" "$real" "$user" "$sys"
    echo
}

echo "Running time benchmarks..."
echo

run_time "Sandmark" "./um um-tests/umbin/sandmark.umz"
run_time "Adventure" "./um um-tests/umbin/advent.umz < adventureScript.txt"
run_time "Midmark" "./um um-tests/umbin/midmark.um"

echo "=============================="
echo " Done"
echo "=============================="