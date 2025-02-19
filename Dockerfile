# Use the latest Ubuntu as the base image
FROM ubuntu:latest

# Set environment variables
ENV DEBIAN_FRONTEND=noninteractive

# Install Clang and essential development tools
RUN apt-get update && apt-get install -y --no-install-recommends \
    clang \
    clang-format \
    clang-tidy \
    lldb \
    cmake \
    make \
    ninja-build \
    build-essential \
    && rm -rf /var/lib/apt/lists/*

# Set Clang as the default compiler
RUN update-alternatives --install /usr/bin/cc cc /usr/bin/clang 100 && \
    update-alternatives --install /usr/bin/c++ c++ /usr/bin/clang++ 100 && \
    update-alternatives --set cc /usr/bin/clang && \
    update-alternatives --set c++ /usr/bin/clang++

# Set working directory
WORKDIR /usr/workspace

# Default command: Open a bash shell
CMD ["/bin/bash"]