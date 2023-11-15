FROM ubuntu:22.04

# zip and unzip are required for the sdkman to be installed from script
RUN \
    apt update && \
    DEBIAN_FRONTEND=noninteractive apt-get install -y \
        build-essential \
        verilator \
        curl \
        zip \ 
        unzip \
        && \
    rm -rf /var/lib/apt/lists/*

# reference: https://sdkman.io/install
RUN curl -s "https://get.sdkman.io" | bash 

# this SHELL command is needed to allow `source` to work properly
# reference: https://stackoverflow.com/questions/20635472/using-the-run-instruction-in-a-dockerfile-with-source-does-not-work/45087082#45087082
SHELL ["/bin/bash", "-c"] 

RUN source "$HOME/.sdkman/bin/sdkman-init.sh" && \
    sdk install java $(sdk list java | grep -o "\b8\.[0-9]*\.[0-9]*\-tem" | head -1) && \
    sdk install sbt

WORKDIR "/root"
COPY . .

ENTRYPOINT ["/bin/bash"]
