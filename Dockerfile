FROM gcc:9.5.0

COPY . /usr/src/File_System

WORKDIR /usr/src/File_System

RUN make build
