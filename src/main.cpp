#include <gtest/gtest.h>
#include "boost/asio.hpp"
#include "boost/beast.hpp"
#include "opencv2/opencv.hpp"
#include "hv/requests.h"
extern "C" {
    #include <libavformat/avformat.h>
}

// 测试 Boost.Asio
TEST(LibraryTest, BoostAsioTest) {
    boost::asio::io_context io_context;
    ASSERT_NO_THROW({
        std::cout << "Boost.Asio io_context created successfully!" << std::endl;
    });
}

// 测试 Boost.Beast
TEST(LibraryTest, BoostBeastTest) {
    boost::beast::http::request<boost::beast::http::string_body> req{boost::beast::http::verb::get, "/", 11};
    req.set(boost::beast::http::field::host, "www.example.com");
    req.set(boost::beast::http::field::user_agent, BOOST_BEAST_VERSION_STRING);
    ASSERT_NO_THROW({
        std::cout << "HTTP GET request created using Boost.Beast!" << std::endl;
    });
}

// 测试 libhv
TEST(LibraryTest, LibhvGetRequestTest) {
    auto resp = requests::get("http://www.example.com");
    ASSERT_NE(resp, nullptr);
    ASSERT_EQ(resp->status_code, 200);
    // std::cout << "Response: " << resp->body << std::endl;
}

// 测试 FFmpeg 版本
TEST(LibraryTest, FFMpegVersionTest) {
    unsigned version = avformat_version();
    std::cout << "FFmpeg version: " << version << std::endl;
    
    // 检查版本号是否大于等于某个已知的版本
    // 例如：检查 FFmpeg 版本是否大于等于 4.0.0 (版本号为 4*10000+0*100+0)
    EXPECT_GE(version, 400000) << "FFmpeg version is too old!";
}

// 测试 FFmpeg 是否支持 H.264 和 H.265 编解码器
TEST(LibraryTest, FFMpegH264H265SupportTest) {
    const AVCodec* codec = nullptr;
    bool h264_found = false;
    bool h265_found = false;

    std::cout << "Checking if FFmpeg supports H.264 and H.265 codecs:" << std::endl;
    
    // 遍历所有注册的编解码器，查找 H.264 和 H.265
    void* i = nullptr;
    while ((codec = av_codec_iterate(&i))) {
        if (strcmp(codec->name, "h264") == 0) {
            h264_found = true;
            std::cout << "H.264 codec found: " << codec->name << " (Type: " 
                      << (codec->type == AVMEDIA_TYPE_VIDEO ? "Video" : "Other") 
                      << ")" << std::endl;
        }
        if (strcmp(codec->name, "hevc") == 0) {
            h265_found = true;
            std::cout << "H.265 codec (HEVC) found: " << codec->name << " (Type: " 
                      << (codec->type == AVMEDIA_TYPE_VIDEO ? "Video" : "Other") 
                      << ")" << std::endl;
        }
    }
    
    // 检查是否找到 H.264 和 H.265
    EXPECT_TRUE(h264_found) << "H.264 codec not found!";
    EXPECT_TRUE(h265_found) << "H.265 codec (HEVC) not found!";
}

// 测试 OpenCV 矩阵操作
TEST(LibraryTest, OpenCVTest) {
    cv::Mat matrix1 = cv::Mat::eye(3, 3, CV_64F);
    cv::Mat matrix2 = cv::Mat::ones(3, 3, CV_64F);
    cv::Mat result = matrix1 + matrix2;

    ASSERT_EQ(matrix1.rows, 3);
    ASSERT_EQ(matrix1.cols, 3);
    ASSERT_EQ(result.at<double>(0, 0), 2.0);  // 检查矩阵加法结果
}

// main 函数：运行所有测试
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
