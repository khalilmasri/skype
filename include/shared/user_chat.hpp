#ifndef USER_CHAT_H
#define USER_CHAT_H

#include "user.hpp"

class UserChat {

public:
  
  UserChat();

  UserChat(const User &t_sender, const User &t_recipient, std::string &t_text,
           bool t_delivered = false);

  UserChat(int t_id, std::string &t_created_at, const User &t_sender,
           const User &t_recipient, std::string &t_text, bool t_delivered = false);

  int           id()    const;
  bool          empty() const;
  std::string   to_string() const; 
  void          from_string(std::string &t_chat);
  std::string   created_at() const;
  int           sender() const;
  int           recipient() const;
  std::string   text() const;
  bool          delivered() const;
  std::size_t   text_length() const;

  static const std::string m_HEADER_DELIM;

  private:
  int           m_id;
  std::string   m_created_at;
  int           m_sender;
  int           m_recipient;
  std::string   m_text;
  bool          m_delivered;
  bool          m_empty;

  static const std::string m_FIELD_DELIM;
};

#endif