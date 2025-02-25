# Use the official GCC image as the base
FROM gcc:latest

# Install additional tools if needed (e.g., build-essential, cmake, gdb)
RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    gdb \
    && rm -rf /var/lib/apt/lists/*

# Set the working directory inside the container
WORKDIR /workspace
