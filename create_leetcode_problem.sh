#!/bin/bash

# Script to create a new LeetCode problem file from template
# Usage: ./create_leetcode_problem.sh <problem_number> <problem_name>
# Example: ./create_leetcode_problem.sh 1 "two-sum"

if [ $# -lt 1 ]; then
    echo "Usage: ./create_leetcode_problem.sh <problem_number> [problem_name]"
    echo "Example: ./create_leetcode_problem.sh 1 \"two-sum\""
    exit 1
fi

PROBLEM_NUM=$1
PROBLEM_NAME=${2:-"problem"}

# Create filename
FILENAME="${PROBLEM_NUM}.${PROBLEM_NAME}.cpp"

# Check if file already exists
if [ -f "$FILENAME" ]; then
    echo "Error: File '$FILENAME' already exists!"
    exit 1
fi

# Copy template
cp .vscode/leetcode_template.cpp "$FILENAME"

# Replace placeholders
if [[ "$OSTYPE" == "darwin"* ]]; then
    # macOS
    sed -i '' "s/PROBLEM_ID/${PROBLEM_NUM}/g" "$FILENAME"
    sed -i '' "s/Problem Name/${PROBLEM_NAME}/g" "$FILENAME"
    sed -i '' "s/problem-slug/${PROBLEM_NAME}/g" "$FILENAME"
else
    # Linux
    sed -i "s/PROBLEM_ID/${PROBLEM_NUM}/g" "$FILENAME"
    sed -i "s/Problem Name/${PROBLEM_NAME}/g" "$FILENAME"
    sed -i "s/problem-slug/${PROBLEM_NAME}/g" "$FILENAME"
fi

echo "✓ Created: $FILENAME"
echo "  Open it in VS Code and type 'lct' to insert the full template, or 'lcs' for simple template"
