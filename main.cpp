#include "frames/frames.hpp"
#include "frames/donut.hpp"
#include "httplib.h"
#include <thread>
#include <chrono>
#include <iostream>

int main() {
    std::unordered_map<std::string, FrameType> FrameMap = {
        {"donut", FrameType{DonutGetFrame, DonutGetLength, DonutGetSleep}}
    };

    httplib::Server svr;

    svr.Get("/:animation", [&FrameMap](const httplib::Request& req, httplib::Response& res) {
        std::string name = req.path_params.at("animation");

        auto it = FrameMap.find(name);
        if (it == FrameMap.end()) {
            res.status = 404;
            res.set_content("Animation not found\n", "text/plain");
            return;
        }
        const FrameType& anim = it->second;

        std::string ua = req.get_header_value("User-Agent");
        if (ua.find("curl") == std::string::npos) {
            res.status = 400;
            res.set_content("Please use curl\n", "text/plain");
            return;
        }

        res.set_chunked_content_provider(
            "text/plain",
            [anim](size_t /*offset*/, httplib::DataSink& sink) -> bool {
                int len = anim.GetLength();
                int sleepMs = anim.GetSleep();

                for (int i = 0; i < len; i++) {
                    std::string_view frame = anim.GetFrame(i);

                    std::string output = "\033[2J\033[H";
                    output += frame;

                    if (!sink.write(output.data(), output.size())) {
                        return false;
                    }

                    std::this_thread::sleep_for(
                        std::chrono::milliseconds(sleepMs)
                    );
                }

                return true;
            }
        );
    });

    if (!svr.listen("0.0.0.0", 8080)) {
        std::cerr << "Error: Failed to start server on port 8080\n";
        return 1;
    }
}