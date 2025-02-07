#!/bin/bash

docker build -t shared_memory .
docker run shared_memory