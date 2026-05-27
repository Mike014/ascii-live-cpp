# Stage 1 — build
FROM ubuntu:22.04 AS builder

RUN apt-get update && apt-get install -y \
    cmake \
    g++ \
    git \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /app
COPY . .

RUN cmake -B build -DCMAKE_BUILD_TYPE=Release -DCMAKE_EXE_LINKER_FLAGS="-static" && \
    cmake --build build

# Stage 2 — runtime
FROM scratch
COPY --from=builder /app/build/ascii-live-cpp /ascii-live-cpp
EXPOSE 8080
CMD ["/ascii-live-cpp"]