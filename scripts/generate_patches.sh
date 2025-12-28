#!/bin/bash

EXERCISE_DIR="exercises"
PATCH_DIR="patches"

# Create patches directory if it doesn't exist
mkdir -p "$PATCH_DIR"

echo ""
echo "Generating patches from '$EXERCISE_DIR'..."
echo "----------------------------------------"

# Check if directory exists
if [ ! -d "$EXERCISE_DIR" ]; then
    echo "Error: Directory '$EXERCISE_DIR' not found."
    exit 1
fi

# Loop through files
for file in "$EXERCISE_DIR"/*; do
    # Skip if not a file
    [ -f "$file" ] || continue

    # Get filename without extension (e.g., test.c -> test)
    filename=$(basename "$file")
    name="${filename%.*}"
    patch_file="$PATCH_DIR/$name.patch"

    # Check for changes (1 = changes, 0 = no changes)
    if ! git diff --quiet "$file"; then
        git diff "$file" > "$patch_file"
        echo "[OK] Created: $patch_file"
    else
        echo "[SKIP] No changes detected in $filename"
    fi
done

echo "----------------------------------------"
echo "Generation complete."
