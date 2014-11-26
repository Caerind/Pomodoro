#!/bin/bash

g++ -std=c++11 main.cpp -I/usr/local/include/SFML -o pomodoro -lsfml-audio -lsfml-graphics -lsfml-window -lsfml-system
sudo cp pomodoro /usr/local/bin/pomodoro
sudo cp ring.wav /usr/local/bin/ring.wav
sudo cp pomodoro.png /usr/local/bin/pomodoro.png
