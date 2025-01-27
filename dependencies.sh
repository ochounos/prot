#!/bin/bash
cd thirdparty
wget https://dl.bintray.com/boostorg/release/1.69.0/source/boost_1_69_0.tar.gz
tar -xvf boost_1_69_0.tar.gz
cd boost_1_69_0
sudo ./bootstrap.sh --with-python=/usr/local/bin/python3 --with-python-version=3.7 --with-python-root=/usr/local/lib/python3.7 --prefix=/usr/
sudo ./b2 clean
sudo ./b2 --enable-unicode=ucs4 -j7 install
