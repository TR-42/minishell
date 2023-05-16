#!/bin/sh

if [ $# -ne 1 ]; then
	echo "usage:" $0 "tester_path" 1>&2
	exit 1
fi

echo "No args"
# no args
$1\
	'abc'\
	'/abc'\
	'$abc/abc'\
	'/abc$abc$dev'\

echo "One args"
# one args
$1\
	'abc def'\
	'/abc $def'\
	'/abc$abc def$def'\
	'/abc$abc$dev def$ghi'\

echo "Redirect / No args"
# one args
$1\
	'abc > def'\
	'/abc <$def'\
	'/abc$abc > def$def'\
	'/abc$abc$dev <def$ghi'\

echo "Redirect / One args"
# one args
$1\
	'abc arg > def'\
	'/abc <$def arg'\
	'/abc$abc arg> def$def'\
	'/abc$abc$dev <def$ghi $arg'\

