#!/bin/bash
SCRIPT=Scph
SCRIPTPATH=${PWD}

echo ""
echo "==============================================================================="
echo "    Setting up paths and environment for "$SCRIPT"."
echo "==============================================================================="
echo ""
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$SCRIPTPATH/lib
export SCPH_DIR=$SCRIPTPATH

