#!/bin/bash

repo_tag=sammyne/wit-bindgen-c-memory-oob

name=demo-wit-bindgen-c-memory-oob

docker run -it --rm                             \
  -e CARGO_HOME=/root/.cargo                    \
  --name $name                                  \
  -v $PWD:/workspace                            \
  -v $PWD/_cargo/registry:/root/.cargo/registry \
  -v $PWD/_cargo/git:/root/.cargo/git           \
  -w /workspace                                 \
  $repo_tag                                     \
    bash -c 'echo "export PATH=/root/.cargo/bin:$PATH" >> /root/.bashrc; bash'