#!/bin/bash

sudo ifconfig enx5882a88b4f28 up
sudo ip addr add 172.26.1.1/12 dev enx5882a88b4f28
sudo sysctl -w net.ipv6.conf.enx5882a88b4f28.disable_ipv6=1
#sudo systemctl disable NetworkManager.service
