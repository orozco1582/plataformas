#!/usr/bin/python
import sys

last_url = None
url_count = 0

max_url = None
max_count = 0

for line in sys.stdin:

    url, count = line.split("\t")

    count = int(count)

    if not last_url:
        last_url = url


    if url == last_url:
        url_count += count
    else:
        if url_count > max_count:
                max_count = url_count
                max_url = last_url
        last_url = url
        url_count = 1

if url_count > max_count:
        result = [last_url, url_count]
        print("\t".join(str(v) for v in result))
else:
        print("\t".join(str(v) for v in [max_url, max_count]))