#!/bin/bash

# Directory to monitor
source_dir="/home/chris/qmk_firmware/keyboards/joyball2"
dest_dir="/home/chris/doc/joyball/v2"

# Function to recursively copy files and directories
function sync_directory() {
  local source="$1"
  local dest="$2"

  echo "Syncing from: $source to: $dest"

  # Create destination directory if it doesn't exist
  mkdir -p "$dest"

  # Iterate over all items (files and directories) in the source directory
  for item in "$source"/*; do
    local base_name="${item##*/}"
    local dest_item="${dest}/${base_name}"

    if [[ -f "$item" ]]; then
      # Handle files
      if [[ ! -f "$dest_item" ]]; then
        echo "Copying new file: $item to $dest_item"
        cp -p "$item" "$dest_item"
      else
        local source_mtime=$(stat -c %Y "$item")
        local dest_mtime=$(stat -c %Y "$dest_item")
        if [[ "$source_mtime" -gt "$dest_mtime" ]]; then
          echo "Copying modified file: $item to $dest_item"
          cp -p "$item" "$dest_item"
        else
          echo "Skipping unmodified file: $item"
        fi
      fi
    elif [[ -d "$item" ]]; then
      # Handle sub-directories recursively
      echo "Entering subdirectory: $item"
      sync_directory "$item" "$dest_item"
    else
      echo "Ignoring special file: $item"
    fi
  done
}

# Start the recursive synchronization
sync_directory "$source_dir" "$dest_dir"

echo "Synchronization complete."

echo "= = = = = = = = = = = = = = = = = ="

qmk compile -kb joyball2 -km default