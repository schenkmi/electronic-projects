#!/usr/bin/env zsh

# Used to regenerate the macOS 26.0+ Liquid Glass icon set, from the single
# .icon file.
#
# Run once, when .icon is updated, and check in the updated icon set.

# Derived from:
# https://www.hendrik-erz.de/post/supporting-liquid-glass-icons-in-apps-without-xcode

ICON_PATH="assets/onerom-liquid-glass.icon"
OUTPUT_PATH="assets/onerom-liquid-glass-icons"
PLIST_PATH="$OUTPUT_PATH/assetcatalog_generated_info.plist"
DEVELOPMENT_REGION="en"

mkdir -p $OUTPUT_PATH

# Adapted from https://github.com/electron/packager/pull/1806/files
actool $ICON_PATH --compile $OUTPUT_PATH \
  --output-format human-readable-text --notices --warnings --errors \
  --output-partial-info-plist $PLIST_PATH \
  --app-icon Icon --include-all-app-icons \
  --enable-on-demand-resources NO \
  --development-region $DEVELOPMENT_REGION \
  --target-device mac \
  --minimum-deployment-target 26.0 \
  --platform macosx

rm $PLIST_PATH