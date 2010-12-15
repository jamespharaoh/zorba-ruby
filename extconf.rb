=begin

  zorba-ruby/extconf.rb

  Copyright 2010 James Pharaoh <james@phsys.co.uk>

  Licensed under the Apache License, Version 2.0 (the "License");
  you may not use this file except in compliance with the License.
  You may obtain a copy of the License at

      http://www.apache.org/licenses/LICENSE-2.0

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.

=end

require "mkmf"
dir_config "zorba"
$LIBS << " -lzorba_simplestore"
create_makefile "zorba"
