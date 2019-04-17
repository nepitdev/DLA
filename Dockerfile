FROM alpine:latest
RUN apk update
RUN apk add g++
RUN apk add libressl-dev
RUN apk add boost-dev
RUN apk add make
COPY project /usr/src/project
WORKDIR /usr/src/project
CMD ["make", "gen-report"]