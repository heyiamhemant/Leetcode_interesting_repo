#!/bin/bash
# Deployment setup for Swing Trader on macOS
#
# Usage: bash deploy/setup.sh

set -e

SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
PROJECT_DIR="$(dirname "$SCRIPT_DIR")"
PLIST_NAME="com.swingtrader.scan"
PLIST_SRC="$SCRIPT_DIR/$PLIST_NAME.plist"
PLIST_DST="$HOME/Library/LaunchAgents/$PLIST_NAME.plist"

echo "=== Swing Trader Deployment ==="
echo "Project: $PROJECT_DIR"

# Create logs directory
mkdir -p "$PROJECT_DIR/logs"

# Install Python dependencies
echo "Installing dependencies..."
pip3 install -r "$PROJECT_DIR/requirements.txt"

# Install launchd plist
echo "Installing launchd agent..."
if launchctl list | grep -q "$PLIST_NAME"; then
    launchctl unload "$PLIST_DST" 2>/dev/null || true
fi

cp "$PLIST_SRC" "$PLIST_DST"

# Update working directory in plist to match actual location
sed -i '' "s|/Users/macandcode/Documents/Leetcode_interesting_repo/swing_trader|$PROJECT_DIR|g" "$PLIST_DST"

launchctl load "$PLIST_DST"

echo ""
echo "Done. Daily scans scheduled at 01:35 IST (Mon-Fri)."
echo ""
echo "Commands:"
echo "  Check status: launchctl list | grep swingtrader"
echo "  View logs:    tail -f $PROJECT_DIR/logs/scan.log"
echo "  Uninstall:    launchctl unload $PLIST_DST && rm $PLIST_DST"
echo ""
echo "Optional env vars (add to ~/.zshrc):"
echo "  export ANTHROPIC_API_KEY='...'     # Claude API fallback"
echo "  export FRED_API_KEY='...'          # Macro data (yield curve, VIX)"
echo "  export TELEGRAM_BOT_TOKEN='...'    # Telegram alerts"
echo "  export TELEGRAM_CHAT_ID='...'      # Telegram alerts"
