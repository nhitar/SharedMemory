#!/bin/bash

sudo docker build -t shared_memory .
sudo docker run shared_memory