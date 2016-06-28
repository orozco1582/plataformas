#!/usr/bin/python
import sys

last_url = None
url_count = 0

for line in sys.stdin:

    line = line.strip()
    url, count = line.split("\t")

    count = int(count)
    # if this is the first iteration
    if not last_url:
        last_url = url

    # if they're the same, log it
    if url == last_url:
        url_count += count
    else:
        # state change (previous line was k=x, this line is k=y)
        result = [last_url, url_count]
        print("\t".join(str(v) for v in result))
        last_url = url
        url_count = 1

# this is to catch the final counts after all records have been received.
print("\t".join(str(v) for v in [last_url, url_count]))