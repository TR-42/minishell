#!/bin/sh

if [ $# -ne 1 ]; then
	echo "usage:" $0 "tester_path" 1>&2
	exit 1
fi

echo "No String"
# no string
$1\
	''\
	'     '\
	'	'\

echo "Simple String"
# simple string
$1\
	'a'\
	'ab'\
	'abc'\
	'a b'\
	'abc defg'\

echo "Some Space Before/After element"
$1\
	' abc'\
	'abc '\
	' abc '\
	' abc defg'\
	'abc defg '\
	' abc defg '\
	' abc  defg '\
	'  abc  defg '\
	'abc  defg  '\
	'  abc  defg  '\

echo "Single/Double Quotes"
$1\
	"'abc'"\
	"'abc defg'"\
	'"abc"'\
	'"abc defg"'\
	'"abc defg""hijk"'\
	"\"abc defg\" 'hijk'"\

echo "Variables"
$1\
	'$ABC'\
	'$$'\
	'$$$'\
	'$$$$'\
	'$$$$$'\
	'$ '\
	'"$ABC"'\
	'"$"'\
	"\"\$'\""\
	'"$ "'\