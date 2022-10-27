#!/bin/bash

if ! [[ -d ./splitDataset ]]
then
  mkdir ./splitDataset;
  g++ split_data.cpp -o splice;
  ./splice;
  rm -fr splice;
fi
