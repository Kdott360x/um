#! /bin/sh

UM=./um
TESTDIR=./um-lab

if [ ! -x "$UM" ] ; then
    echo "Error: $UM not found or not executable"
    exit 1
fi

if [ ! -d "$TESTDIR" ] ; then
    echo "Error: $TESTDIR not found"
    exit 1
fi

for test in "$TESTDIR"/*.um ; do
    base=$(basename "$test" .um)

    echo "===== Running $base.um ====="

    if [ -f "$TESTDIR/$base.0" ] ; then
        "$UM" "$test" < "$TESTDIR/$base.0" > "$TESTDIR/$base.out"
    else
        "$UM" "$test" < /dev/null > "$TESTDIR/$base.out"
    fi

    if [ -f "$TESTDIR/$base.1" ] ; then
        if cmp -s "$TESTDIR/$base.out" "$TESTDIR/$base.1" ; then
            echo "PASS: $base.um"
        else
            echo "FAIL: $base.um"
            echo "expected:"
            cat "$TESTDIR/$base.1"
            echo
            echo "got:"
            cat "$TESTDIR/$base.out"
            echo
        fi
    else
        if [ -s "$TESTDIR/$base.out" ] ; then
            echo "FAIL: $base.um"
            echo "expected no output"
            echo "got:"
            cat "$TESTDIR/$base.out"
            echo
        else
            echo "PASS: $base.um"
        fi
    fi
done