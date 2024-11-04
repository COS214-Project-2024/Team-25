#!/bin/bash

# Path to the file that contains messages
MESSAGE_FILE="temp_messages.txt"

# Infinite loop to keep the script running
while true; do
    # Clear the terminal
    clear

    # Check if the message file exists
    if [[ -f "$MESSAGE_FILE" ]]; then
        # Display the contents of the message file
        cat "$MESSAGE_FILE"
    else
        echo "Message file not found: $MESSAGE_FILE"
    fi

    # Wait for 1 second
    sleep 1
done