FROM alpine:latest
WORKDIR /app
COPY server .
RUN gcc server/*.c -o server
CMD ["./server"]