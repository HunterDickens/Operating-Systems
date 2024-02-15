#!/bin/bash

# Compile the producer and consumer programs
gcc producer.c -o producer
gcc consumer.c -o consumer

# Check if the producer executable was created successfully
if [ -f ./producer ]; then
    echo "Running the producer..."
    ./producer
else 
    echo "Failed to compile the producer."
    exit 1
fi

# Check if the consumer executable was created successfully
if [ -f ./consumer ]; then
    echo "Running the consumer..."
    ./consumer
else 
    echo "Failed to compile the consumer."
    exit 1
fi

# Compile the unixpipe program
gcc unixpipe.c -o unixpipe

# Check if the unixpipe executable was created successfully
if [ -f ./unixpipe ]; then
    echo "Running the unixpipe program..."
    ./unixpipe
else 
    echo "Failed to compile unixpipe."
    exit 1
fi

# Run the Python server
echo "Starting the Python server..."
python3 server.py &

# Give the server some time to start
sleep 2

# Run the Python client
echo "Running the Python client..."
python3 client.py

# Kill the server process
echo "Stopping the Python server..."
pkill -f server.py
