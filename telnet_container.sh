#!/bin/sh

docker build -t my-telnet telnet

docker run -it --rm my-telnet /bin/sh