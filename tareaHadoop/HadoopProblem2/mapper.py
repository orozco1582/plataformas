#!/usr/bin/python
import sys

for line in sys.stdin:
	line.replace("\t", ",")
	
	line = line.strip()
    unpacked = line.split(",")
    host, logname, time, method, url, response, bytes = line.split(",")
    #stadium, capacity, expanded, location, surface, turf, team, opened, weather, roof, elevation = line.split(",")
    if host == "edams.ksc.nasa.gov":
    	results = [url, "1"]
    #results = [turf, "1"]
    print("\t".join(results))