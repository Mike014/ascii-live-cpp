# ascii-live-cpp

A C++ port of [ascii-live](https://github.com/hugomd/ascii-live) — stream ASCII animations directly in your terminal via `curl`.

```
curl http://localhost:8080/donut
```

---

## Quick Start

### Run with Docker

```bash
docker run -p 8080:8080 mike014/ascii-live-cpp:latest
```

Then in a second terminal:

```bash
curl http://localhost:8080/donut
```

> Requires curl. Browser requests return HTTP 400.

---

## Available Animations

| Path | Animation |
|------|-----------|
| `/donut` | Rotating donut |

More animations coming soon.

---

## Build from Source

**Requirements:** CMake 3.14+, GCC/G++ with C++17 support, Git

```bash
git clone https://github.com/Mike014/ascii-live-cpp.git
cd ascii-live-cpp
mkdir build && cd build
cmake .. -G "MinGW Makefiles"   # Windows
# cmake ..                      # Linux/macOS
cmake --build .
./ascii-live-cpp.exe            # Windows
# ./ascii-live-cpp              # Linux/macOS
```

Dependencies are downloaded automatically at configure time via CMake FetchContent ([cpp-httplib v0.18.3](https://github.com/yhirose/cpp-httplib)).

---

## Project Structure

```
ascii-live-cpp/
├── CMakeLists.txt
├── Dockerfile
├── main.cpp
├── frames/
│   ├── frames.hpp       — FrameType struct + FrameMap
│   └── donut.hpp        — 12 ASCII frames + accessor functions
└── .github/
    └── workflows/
        └── main.yml     — CI/CD: build + push to Docker Hub
```

---

## How It Works

- HTTP server built with [cpp-httplib](https://github.com/yhirose/cpp-httplib)
- Each request streams frames via **chunked transfer encoding**
- Terminal is cleared between frames using ANSI escape codes (`\033[2J\033[H`)
- Client disconnect is detected via `sink.write` return value
- User-Agent check enforces `curl` only

---

## Docker Image

The image uses a **multi-stage build**:

- **Stage 1 (builder):** Alpine 3.19 with musl-libc — compiles a fully static binary
- **Stage 2 (runtime):** `scratch` — zero OS overhead, binary only

```bash
docker pull mike014/ascii-live-cpp:latest
```

---

## CI/CD

Every push to `main` triggers a GitHub Actions workflow that builds the Docker image and pushes it to Docker Hub with two tags:

- `mike014/ascii-live-cpp:latest`
- `mike014/ascii-live-cpp:{git-sha8}`

---

## Documentation

Full build log, architecture decisions, and troubleshooting notes:
[ascii-live-cpp — Project Build Recap](https://docs.google.com/document/d/1ioPLJBcVrio644KOlqCbIu5Pfdmz0YGz3vxdW4ywFFY/edit?tab=t.0)

---

## License

MIT
