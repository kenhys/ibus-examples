#!/bin/bash

#set -x
case $1 in
    debug)
        G_MESSAGES_DEBUG="all" ./ibus-engine-radiomenuimeonoff2 2>&1 | tee test.log
        ;;
    *)
        ./ibus-engine-radiomenuimeonoff2 2>&1 | tee test.log
        ;;
esac
