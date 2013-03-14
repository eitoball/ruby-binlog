require 'mkmf'

if have_library('stdc++') and have_library('replication') and have_header('stdint.h')
  have_func('rb_thread_blocking_region')
  create_makefile('binlog')
end
