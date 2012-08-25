#ifndef __RUBY_BINLOG_EVENT_H__
#define __RUBY_BINLOG_EVENT_H__

#include "ruby_binlog.h"

extern VALUE rb_cBinlogEvent;

namespace ruby {
namespace binlog {

struct Event {
  mysql::Log_event_header *m_event_header;

  static VALUE get_marker(VALUE self);
  static VALUE get_timestamp(VALUE self);
  static VALUE get_type_code(VALUE self);
  static VALUE get_server_id(VALUE self);
  static VALUE get_event_length(VALUE self);
  static VALUE get_next_position(VALUE self);
  static VALUE get_flags(VALUE self);
  static VALUE get_event_type(VALUE self);
  static void init(VALUE clazz);
};

struct QueryEvent : public Event {
  mysql::Query_event *m_event;

  static void free(QueryEvent *p);
  static VALUE alloc(VALUE klass);
  static void set_event(VALUE self, mysql::Binary_log_event *event);
  static void init();

  static VALUE get_thread_id(VALUE self);
  static VALUE get_exec_time(VALUE self);
  static VALUE get_error_code(VALUE self);
  static VALUE get_variables(VALUE self);
  static VALUE get_db_name(VALUE self);
  static VALUE get_query(VALUE self);
};

struct RotateEvent : public Event {
  mysql::Rotate_event *m_event;

  static void free(RotateEvent *p);
  static VALUE alloc(VALUE klass);
  static void set_event(VALUE self, mysql::Binary_log_event *event);
  static void init();

  static VALUE get_binlog_file(VALUE self);
  static VALUE get_binlog_pos(VALUE self);
};

struct FormatEvent : public Event {
  mysql::Format_event *m_event;

  static void free(FormatEvent *p);
  static VALUE alloc(VALUE klass);
  static void set_event(VALUE self, mysql::Binary_log_event *event);
  static void init();

  static VALUE get_binlog_version(VALUE self);
  static VALUE get_master_version(VALUE self);
  static VALUE get_created_ts(VALUE self);
  static VALUE get_log_header_len(VALUE self);
};

struct UserVarEvent : public Event {
  mysql::User_var_event *m_event;

  static void free(UserVarEvent *p);
  static VALUE alloc(VALUE klass);
  static void set_event(VALUE self, mysql::Binary_log_event *event);
  static void init();

  static VALUE get_name(VALUE self);
  static VALUE get_is_null(VALUE self);
  static VALUE get_type(VALUE self);
  static VALUE get_charset(VALUE self);
  static VALUE get_value(VALUE self);
};

struct UnimplementedEvent : public Event {
  mysql::Binary_log_event *m_event;

  static void free(QueryEvent *p);
  static VALUE alloc(VALUE klass);
  static void set_event(VALUE self, mysql::Binary_log_event *event);
  static void init();
};

} // namespace binlog
} // namespace ruby

#endif // __RUBY_BINLOG_EVENT_H__
