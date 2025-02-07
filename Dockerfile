FROM gcc:11.3.0

WORKDIR /docker

COPY ./src/shared_memory_creator.c /docker/src/shared_memory_creator.c
COPY ./src/shared_memory_reader.c /docker/src/shared_memory_reader.c

RUN gcc ./src/shared_memory_creator.c -o creator 
RUN gcc ./src/shared_memory_reader.c -o reader

CMD ["sh", "-c", "./creator | ./reader"]