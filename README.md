# netmap

Vizualizing traffic between network nodes.

Each vertex is a host, each edge represents traffic between nodes - the thicker the line - more traffic going on between nodes at a moment.

# Plan

Proof of concept:

1. Backend to store metrics (e.g. metrics for specific node might look like timestamp -> bandwidth)
1. Web page where user chooses a time range and hits the "Go" button
1. Web server underneath gets a file in a format below from backend (possibly from any source) and outputs an animated graph (possibly backed by sigma.js)

Format
```
'<timestamp>': [
	{ from: '<dns_or_ip>', to: '<dns_or_ip>', KBsPerSec=<KB/s> },
	...
]
...
```

# Backend

Pillars:

1. Append-only storage
  1. Index is stored as an array that constantly grows up
  1. Each element contains timestamp and offset in data file
  1. Naturally the array is sorted by timestamp
  1. Data file grows the same way but contains variable amount of data per entry - it contains timestamp and array of edges

1. Storage accumulates all requests within 1 sec range and create only 1 record per second
  1. 2.6M of record per month - index grows by ~40MB / month. Should separate index file by months.

1. Storage discards new data from the past (if received after the last 1 sec range but with timestamp <= it)

1. Push model
  1. ASCII protocol

1. One-thread no-locks epoll model

