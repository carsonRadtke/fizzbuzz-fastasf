# Fizz Buzz Fast as F*ck
High throughput Fizz Buzz

https://codegolf.stackexchange.com/questions/215216/high-throughput-fizz-buzz

There have been several improvements from the naive implementation.
Namely: 
- manual loop unraveling
- custom buffering for `write(2)` instead of `printf(3)`

This has increased the throughput from 236 MiB/s to 1.04 GiB/s.

In the future I'd like to come back to this and see what I can doing using vector
operations.
