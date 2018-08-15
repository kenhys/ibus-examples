#!/bin/bash

#set -x
case $1 in
    debug)
        G_MESSAGES_DEBUG="all" ./radiomenustall 2>&1 | tee test.log
        ;;
    *)
        ./radiomenustall 2>&1 | tee test.log
        ;;
esac
