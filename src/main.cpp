#include <iostream>
#include "boost/asio.hpp"
#include "boost/beast.hpp"
#include "opencv2/opencv.hpp"

int main() {
    // 使用 Boost.Asio 创建一个 I/O 服务对象
    boost::asio::io_context io_context;
    std::cout << "Boost.Asio io_context created successfully!" << std::endl;

    // 使用 Boost.Beast 创建一个 HTTP GET 请求（示例）
    boost::beast::http::request<boost::beast::http::string_body> req{boost::beast::http::verb::get, "/", 11};
    req.set(boost::beast::http::field::host, "www.example.com");
    req.set(boost::beast::http::field::user_agent, BOOST_BEAST_VERSION_STRING);
    std::cout << "HTTP GET request created using Boost.Beast!" << std::endl;

    // 测试 OpenCV 读取并显示图片
    cv::Mat image = cv::imread("/mnt/c/Users/77275/Desktop/1e30e924b899a901b92d46af1d950a7b0208f50b.png");
    if (image.empty()) {
        std::cerr << "Could not open or find the image!" << std::endl;
        return -1;
    }

    cv::imshow("Display Image", image);
    cv::waitKey(0); // 等待按键
    return 0;
}
