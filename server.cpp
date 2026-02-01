#include "httplib.h"
#include <nlohmann/json.hpp>
#include <fstream>
#include <iostream>
#include <string>
using json = nlohmann::json;

std::string unescape(const std::string& s) {
    std::string r;
    for (size_t i = 0; i < s.size(); i++) {
        if (s[i] == '\\' && i + 1 < s.size()) {
            if (s[i + 1] == 'n') {
                r += '\n'; i++;
            } else if (s[i + 1] == 't') {
                r += '\t'; i++;
            } else if (s[i + 1] == '\\') {
                r += '\\'; i++;
            } else {
                r += s[i];
            }
        } else r += s[i];
    }
    return r;
}

int main() {
    httplib::Server svr;

    svr.Post("/", [](const httplib::Request& req, httplib::Response& res) {
        auto data = json::parse(req.body);
        auto tests = data["tests"];

        std::ofstream f("tests.db");
        for (auto& t : tests) {
            std::string in = t["input"].get<std::string>();
            std::string out = t["output"].get<std::string>();

            f << "###\n" << unescape(in) << "\n@@@\n" << unescape(out) << std::endl;
        }
        f.close();

        res.set_content("OK", "text/plain");
    });

    std::cout << "starting server...\n";
    bool ok = svr.listen("0.0.0.0", 27122);

    if (!ok) {
        std::cerr << "Failed to bind to port 27122\n";
        return 1;
    }

    return 0;
}

