FROM alpine:3.18.4

RUN apk update && apk add busybox-extras

EXPOSE 8080
CMD ["telnetd", "-F"]