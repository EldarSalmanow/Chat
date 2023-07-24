#include <boost/asio.hpp>

#include <GSCrossPlatform/CrossPlatform.h>

std::string readSocket(LRef<boost::asio::ip::tcp::socket> socket) {
    boost::asio::streambuf buffer;

    boost::asio::read_until(socket,
                            buffer,
                            '\n');

    std::string message = boost::asio::buffer_cast<const char *>(buffer.data());

    if (!message.empty()) {
        message.pop_back();
    }

    return message;
}

Void writeSocket(LRef<boost::asio::ip::tcp::socket> socket,
                 ConstLRef<std::string> message) {
    boost::asio::write(socket,
                       boost::asio::buffer(message + '\n'));
}

I32 main(I32 argc,
         Ptr<Ptr<C>> argv) {
    boost::asio::io_context context;
    boost::asio::ip::tcp::endpoint address(boost::asio::ip::address::from_string("127.0.0.1"),
                                           9999);
    boost::asio::ip::tcp::acceptor acceptor(context,
                                            address);
    boost::asio::ip::tcp::socket socket(context);

    acceptor.accept(socket);

    auto name = readSocket(socket);

    auto message = "Привет, " + name + "!";

    std::cout << "Сервер: " << message << std::endl;

    writeSocket(socket,
                message);

    while (true) {
        auto response = readSocket(socket);

        if (response == "exit") {
            std::cout << name << " покинул чат!" << std::endl;

            break;
        }

        std::cout << name << ": " << response << std::endl;
        std::cout << "Сервер: ";
        std::getline(std::cin,
                     message);

        writeSocket(socket,
                    message);

        if (message == "exit") {
            break;
        }
    }

    return 0;
}
