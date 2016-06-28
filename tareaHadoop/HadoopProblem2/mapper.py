#!/usr/bin/python
import sys

for line in sys.stdin:

    host, logname, time, method, url, response, size = line.split("\t")[0:7]

    if host == "edams.ksc.nasa.gov":
        results = [url, "1"]
        print("\t".join(results))