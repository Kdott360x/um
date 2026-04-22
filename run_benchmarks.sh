#!/usr/bin/env bash
# THESE ARE OUR BENCHMARK TESTS
# THEY INCLUDE A SMALL MEDIUM AND LARGE TEST
# SMALL - midmark.um
# MEDIUM - advent.ums < adventureScript.txt , this is the adventure game with the script from the spec
# LARGE - sandmark.umz
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