#!/bin/bash
export GAME="/d/Program Files (x86)/Activision/Cod4Mod"
export WORKDIR="mods/sr_speedrun/scripts"
export SERVER="start.sh"
export CLIENT="client.sh"

cd "$GAME/$WORKDIR"

start $CLIENT
./$SERVER
