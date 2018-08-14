#!/bin/bash

#set -x
case $1 in
    debug)
        G_MESSAGES_DEBUG="all" ./ibus-engine-radiomenudelay 2>&1 | tee test.log
        ;;
    *)
        ./ibus-engine-radiomenudelay 2>&1 | tee test.log
        ;;
esac
