FROM alpine:latest
RUN apk update
RUN apk add g++
RUN apk add libressl-dev
RUN apk add boost-dev
RUN apk add make
COPY src /usr/src/project/src
COPY tests /usr/src/project/tests
COPY Makefile /usr/src/project/Makefile
WORKDIR /usr/src/project
CMD ["make", "gen-report"]