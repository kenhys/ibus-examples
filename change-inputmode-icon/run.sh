#!/bin/bash

#set -x
case $1 in
    debug)
        G_MESSAGES_DEBUG="all" ./ibus-engine-changeinputmodeicon 2>&1 | tee test.log
        ;;
    *)
        ./ibus-engine-changeinputmodeicon 2>&1 | tee test.log
        ;;
esac
