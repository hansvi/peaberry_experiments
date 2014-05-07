#!/bin/bash
#
# Repeatedly increase the frequency of the peaberry.
# Uses the hamlib rigctl utility (some good soul added peaberry support to hamlib :-))

for i in `seq 14050000 2000 14200000`;
do
	rigctl -m 2517 F $i
	sleep 1
done

