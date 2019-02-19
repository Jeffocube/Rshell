#!/bin/sh
echo "testing: echo exit, echo hello world || exit && echo hi, echo hello world && exit"
.././rshell < exit.txt
echo "testing: ls || exit || exit && exit, echo hi exit"
.././rshell < exit2.txt
echo "testing: exit"
.././rshell < exit3.txt