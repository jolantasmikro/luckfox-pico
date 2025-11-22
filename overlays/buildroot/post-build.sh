#!/bin/bash

# Nukopijuoti RkLunch.sh po viso kompiliavimo
cp -f ${BR2_EXTERNAL_PATH:-$(dirname $0)}/oem/usr/bin/RkLunch.sh   ${TARGET_DIR}/oem/usr/bin/RkLunch.sh

chmod +x ${TARGET_DIR}/oem/usr/bin/RkLunch.sh

echo "RkLunch.sh updated from overlay"