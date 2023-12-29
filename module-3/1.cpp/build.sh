#!/bin/bash

rm -f -- result
g++ realization/main.cpp realization/ListGraph.cpp realization/ArcGraph.cpp realization/MatrixGraph.cpp realization/SetGraph.cpp -o result

if [ -f result ]; then
  ./result
fi
