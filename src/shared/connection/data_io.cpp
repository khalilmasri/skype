#include "data_io.hpp"
#include "connection.hpp"
#include "string_utils.hpp"
#include "text_data.hpp"
#include <cstring>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>


#include <errno.h>

#define BUFFER_SIZE 512

bool DataIO::respond(Request &t_req) const {

  auto[ip, port] = StringUtils::split_first(t_req.m_address,":");

  std::string data = TextData::to_string(t_req.data());
  char buffer[BUFFER_SIZE] = {0};
  memcpy(buffer , data.c_str(), data.size());

  sockaddr_in addr_in = Connection::to_sockaddr_in(port, ip);

 int res = sendto(t_req.m_socket, buffer, BUFFER_SIZE, 0,
      reinterpret_cast<struct sockaddr *>(&addr_in), sizeof(addr_in));

  t_req.m_valid = is_valid(res, "DataIO could not send.");

  return t_req.m_valid;
};


bool DataIO::receive(Request &t_req) const {

  char buffer[BUFFER_SIZE] = {0};

  sockaddr_in addr_in;
  socklen_t addr_len = sizeof(addr_in);

  int res = recvfrom(t_req.m_socket, buffer, BUFFER_SIZE, 0,
      reinterpret_cast<struct sockaddr *>(&addr_in), &addr_len);

  t_req.m_valid =  is_valid(res, "DataIO could not receive.");

 if(t_req.m_valid){

  t_req.m_address = Connection::address_tostring(addr_in)
    + ":"
    + Connection::port_tostring(addr_in); ;

   std::cout << t_req.m_address << std::endl;
  t_req.set_data(new TextData(buffer));
 }

  return t_req.m_valid; 
};


// TODO: MANAGED TO SEND. needs to test receive and set up the punch hole UDP
