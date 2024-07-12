#!/bin/bash

cd `dirname ${BASH_SOURCE[0]}`

repo_tag=sammyne/wit-bindgen-c-memory-oob

docker build -t $repo_tag .

