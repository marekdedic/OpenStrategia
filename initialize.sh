#!/bin/bash
# Installs all needed libraries.
# Written for Ubuntu, other distros might need minor changes (replacing apt with yum etc.).

DEPENDENCIES="build-essential libglew-dev libglfw3-dev libglm-dev libfreetype6-dev"

printf "This script will install all libraries needed to build OpenStrategia. \033[0;31mThis may take quite some time.\033[0m For this, it also needs to run some commands as a \033[0;36msuper-user\033[0m. Feel free to inspect the code in \"initialize.sh\".\n"

sudo apt-get update
sudo apt-get install -y $DEPENDENCIES

