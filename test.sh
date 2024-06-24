#!/bin/bash -
#===============================================================================
#
#          FILE: test.sh
#
#         USAGE: ./test.sh
#
#   DESCRIPTION: 
#
#       OPTIONS: ---
#  REQUIREMENTS: ---
#          BUGS: ---
#         NOTES: ---
#        AUTHOR: fatmeat (), pathofyggdrasil@gmail.com
#  ORGANIZATION: 
#       CREATED: 06/24/24 15:51:37
#      REVISION:  ---
#===============================================================================

set -o nounset                                  # Treat unset variables as an error

make
./create_iso.sh
./launch.sh

