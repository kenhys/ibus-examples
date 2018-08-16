#!/bin/bash

#set -x
case $1 in
    debug)
        G_MESSAGES_DEBUG="all" ./ibus-engine-radiomenunoneedtoupdate 2>&1 | tee test.log
        ;;
    *)
        ./ibus-engine-radiomenunoneedtoupdate 2>&1 | tee test.log
        ;;
esac
