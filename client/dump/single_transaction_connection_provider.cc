/*
  Copyright (c) 2015, Oracle and/or its affiliates. All rights reserved.

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; version 2 of the License.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301  USA
*/

#include "single_transaction_connection_provider.h"

using namespace Mysql::Tools::Dump;

Mysql::Tools::Base::Mysql_query_runner*
  Single_transaction_connection_provider::create_new_runner(
    Mysql::I_callable<bool, const Mysql::Tools::Base::Message_data&>*
      message_handler)
{
  Mysql::Tools::Base::Mysql_query_runner* runner=
    Thread_specific_connection_provider::create_new_runner(message_handler);
  runner->run_query(
    "SET SESSION TRANSACTION ISOLATION LEVEL REPEATABLE READ");
  runner->run_query(
    "START TRANSACTION /*!40100 WITH CONSISTENT SNAPSHOT */");
  return runner;
}

Single_transaction_connection_provider::Single_transaction_connection_provider(
  Mysql::Tools::Base::I_connection_factory* connection_factory)
  : Thread_specific_connection_provider(connection_factory)
{}
