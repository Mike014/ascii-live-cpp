# Stage 1 — build with musl (Alpine)
FROM alpine:3.19 AS builder

RUN apk add --no-cache cmake g++ git make

WORKDIR /app
COPY . .

RUN cmake -B build -DCMAKE_BUILD_TYPE=Release \
        -DCMAKE_EXE_LINKER_FLAGS="-static" && \
    cmake --build build

# Stage 2 — runtime scratch
FROM scratch
COPY --from=builder /app/build/ascii-live-cpp /ascii-live-cpp
EXPOSE 8080
CMD ["/ascii-live-cpp"]