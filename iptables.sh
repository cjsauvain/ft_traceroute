#!/bin/bash

if [ $1 = "disable_sending" ]; then
	sudo iptables -A OUTPUT -p udp -o $2 -j DROP
	echo "* sending disabled *"
elif [ $1 = "enable_sending" ]; then
	sudo iptables -D OUTPUT -p udp -o $2 -j DROP
	echo "* sending enabled *"
elif [ $1 = "disable_receiving" ]; then
	sudo iptables -A INPUT -p icmp -j DROP
	echo "* receiving disabled *"
elif [ $1 = "enable_receiving" ]; then
	sudo iptables -A INPUT -p icmp -j DROP
	echo "* receiving enabled *"
fi
