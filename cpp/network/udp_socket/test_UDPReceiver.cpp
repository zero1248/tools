#include <iostream>
#include <fstream>
#include "UDPReceiver.h"


int main(int argc, char* argv[]) {
    try {

        // 解析命令行参数
        if (argc < 2) {
            std::cerr << "Usage: " << argv[0] << " <port> [output_file]\n"
                      << "Example: " << argv[0] << " 4096 udp_data.bin\n";
            return 1;
        }

        // 转换并验证端口号
        int port;
        try {
            port = std::stoi(argv[1]);
        } catch (const std::exception& e) {
            std::cerr << "Invalid port number: " << argv[1] << "\n";
            return 1;
        }
        if (port < 1 || port > 65535) {
            std::cerr << "Port must be between 1 and 65535\n";
            return 1;
        }

        // 解析文件名参数
        std::string output_file_name;
        if(argc == 3) {
            output_file_name = argv[2];
        }



        UDPReceiver receiver(port);
        receiver.Start();

        // 主循环处理数据
        while (true) {
            auto data = receiver.GetData();
            if (!data.empty()) {
                // 在此处处理接收到的数据
                std::cout << "Processing " << data.size() << " bytes of data" << std::endl;
                std::cout << data.data() << std::endl;

                if(argc == 3) {
                    std::ofstream outfile(output_file_name, std::ios::binary | std::ios::app);
                    if (!outfile.is_open()) {
                        std::cerr << "Cannot open output file: " << output_file_name << std::endl;
                        return 1;
                    }
                    // save data to file
                    outfile.write(reinterpret_cast<const char*>(data.data()), data.size());
                    outfile << std::endl;
                    if (!outfile) {
                        std::cerr << "File write failed!" << std::endl;
                        break;
                    }
                    // flush buffer to ensure data persistence
                    outfile.flush(); 
                }
                
                // 示例：将数据写入文件（可选）
                // std::ofstream("udp_data.bin", std::ios::app).write(
                //     reinterpret_cast<char*>(data.data()), data.size());
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}






