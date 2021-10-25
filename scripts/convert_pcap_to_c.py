#! /usr/bin/env python3
import os
import re
import argparse

def get_args():
    parser = argparse.ArgumentParser(description='Program to convert pcap to c for writeup1')
    parser.add_argument('-p', '--path', type=str, metavar='PATH', help='Path to the folder')
    args = parser.parse_args()
    return args

def converter(path):
    results = {}
    for file in os.listdir(path):
      with open(os.path.join(path, file), 'r') as f:
          content = f.read()
          f.close()
          line = re.search(r'//file([0-9]*)', content)
          index = int(line.group(1))
          results[index] = content
    sortedResults = sorted(results.items())

    newFile = open("main.c", "w")
    for key, value in sortedResults:
        newFile.write(f'{value}\n')
    newFile.close()

if __name__ == '__main__':
    args = get_args()
    if (args.path):
        converter(args.path)