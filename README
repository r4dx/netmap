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
