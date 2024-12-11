FROM ubuntu:20.04

# Set non-interactive mode and set timezone to avoid prompts
ENV DEBIAN_FRONTEND=noninteractive
ENV TZ=Asia/Manila 

# Install Wine and other dependencies
RUN dpkg --add-architecture i386 && \
    apt-get update && \
    apt-get install -y --no-install-recommends \
    wine64 \
    wine32 \
    build-essential \
    libsdl2-dev \
    libsdl2-image-dev \
    libsdl2-mixer-dev \
    tzdata && \
    rm -rf /var/lib/apt/lists/*

WORKDIR /app

# Copy files to the container
COPY SDL_TEMPLATE /app/SDL_TEMPLATE/
COPY x64/Debug/Inferno_Shooter.exe /app/
COPY x64/Debug/assets /app/assets
COPY x64/Debug/*.dll /app/

CMD ["wine", "Inferno_Shooter.exe"]
