FROM busybox:1.36.1 AS wasi-sdk

ARG MAJOR_VERSION=22 \
  MINOR_VERSION=0

WORKDIR /output

RUN wget https://github.com/WebAssembly/wasi-sdk/releases/download/wasi-sdk-$MAJOR_VERSION/wasi-sdk-$MAJOR_VERSION.$MINOR_VERSION-linux.tar.gz

RUN tar xvf wasi-sdk-$MAJOR_VERSION.$MINOR_VERSION-linux.tar.gz

RUN mv wasi-sdk-$MAJOR_VERSION.$MINOR_VERSION wasi-sdk


FROM busybox:1.36.1 AS wasmtime

ARG WASMTIME_VERSION=22.0.0

ENV REPO_URL=https://github.com/bytecodealliance/wasmtime/releases/download/v$WASMTIME_VERSION

RUN wget $REPO_URL/wasmtime-v$WASMTIME_VERSION-x86_64-linux.tar.xz

RUN mkdir -p /output && tar -C /output --strip-components 1 -Jxvf wasmtime-v$WASMTIME_VERSION-x86_64-linux.tar.xz

WORKDIR /output/adapter-modules

RUN wget $REPO_URL/wasi_snapshot_preview1.command.wasm  &&\
  wget $REPO_URL/wasi_snapshot_preview1.proxy.wasm      &&\
  wget $REPO_URL/wasi_snapshot_preview1.reactor.wasm


FROM rust:1.79.0-bookworm

ENV RUSTUP_DIST_SERVER=https://rsproxy.cn       \
  RUSTUP_UPDATE_ROOT=https://rsproxy.cn/rustup

#RUN rustup default nightly-2024-06-10

RUN cargo install wasm-tools@1.212.0 wit-bindgen-cli@0.27.0

RUN sed -i 's/deb.debian.org/mirrors.tencent.com/g' /etc/apt/sources.list.d/debian.sources  &&\
  sed -i 's|security.debian.org/debian-security|mirrors.tencent.com/debian-security|g' /etc/apt/sources.list.d/debian.sources

ENV PATH=$PATH:/opt/wasmtime:/opt/wasi-sdk/bin

COPY --from=wasmtime /output /opt/wasmtime

COPY --from=wasi-sdk /output/wasi-sdk /opt/wasi-sdk

