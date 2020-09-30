#!/bin/bash

# Get number of instances running
NUM_BGPD=$(ps ux | grep bgpd | grep -v "grep\|watchfrr" | wc -l)
NUM_OSPFD=$(ps ux | grep ospfd | grep -v "grep\|watchfrr" | wc -l)
NUM_ZEBRA=$(ps ux | grep zebra | grep -v "grep\|watchfrr" | wc -l)
NUM_WATCHFRR=$(ps ux | grep watchfrr | grep -v "grep" | wc -l)

# Check BGP is running
if [[ ${NUM_BGPD} != 1 ]];
then
	exit 1
fi

# Check OSPF is running
if [[ ${NUM_OSPFD} != 1 ]];
then
	exit 1
fi

# Check RIP is running
if [[ ${NUM_RIPD} != 1 ]];
then
	exit 1
fi

# Check EIGRP is running
if [[ ${NUM_EIGRPD} != 1 ]];
then
	exit 1
fi

# Check ZEBRA is running
if [[ ${NUM_ZEBRA} != 1 ]];
then
	exit 1
fi

# Check WATCHFRR is running
if [[ ${NUM_WATCHFRR} != 1 ]];
then
	exit 1
fi

exit 0
