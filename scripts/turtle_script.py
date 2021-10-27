#! /usr/bin/env python3
import turtle
import time
import re

file = open("turtle", "r")
content = file.read()
file.close()
lines = content.split('\n')

turtle.setup(width = 1000, height = 1000, startx = 0, starty = 0)
turtle.speed(100000)

for step in lines:
    match = re.search(r'\d+', step)
    if (match):
        number = int(match.group(0))
        if "gauche" in step:
            turtle.lt(number)
        elif "droite" in step:
            turtle.rt(number)
        elif "Avance" in step:
            turtle.fd(number)
        elif "Recule" in step:
            turtle.bk(number)

time.sleep(10)