FROM registry.gitlab.com/solidtux/devimages/python-uv
RUN apt update && \
    apt install -y gcc-arm-none-eabi avrdude gcc-avr dfu-programmer dfu-util dos2unix && \
    rm -rf /var/lib/apt/lists/*
