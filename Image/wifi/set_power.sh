#!/bin/sh

uci set wireless.radio0.txpower=$1
uci commit wireless
wifi up
