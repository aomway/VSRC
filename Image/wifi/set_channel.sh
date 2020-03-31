#!/bin/sh

uci set wireless.radio0.channel=$1
uci commit wireless
wifi up
