/**
 * Copyright (c) 2011-2015 libbitcoin developers (see AUTHORS)
 *
 * This file is part of libbitcoin.
 *
 * libbitcoin is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License with
 * additional permissions to the one published by the Free Software
 * Foundation, either version 3 of the License, or (at your option)
 * any later version. For more information see LICENSE.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */
#include <bitcoin/bitcoin/network/protocol_base.hpp>

#include <string>
#include <bitcoin/bitcoin/config/authority.hpp>
#include <bitcoin/bitcoin/error.hpp>
#include <bitcoin/bitcoin/network/channel.hpp>
#include <bitcoin/bitcoin/utility/dispatcher.hpp>
#include <bitcoin/bitcoin/utility/threadpool.hpp>

namespace libbitcoin {
namespace network {

protocol_base::protocol_base(threadpool& pool, channel::ptr channel,
    const std::string& name)
  : pool_(pool), dispatch_(pool), channel_(channel), name_(name)
{
}

config::authority protocol_base::authority() const
{
    return channel_->authority();
}

const std::string& protocol_base::name()
{
    return name_;
}

uint64_t protocol_base::nonce()
{
    return channel_->nonce();
}

threadpool& protocol_base::pool()
{
    return pool_;
}

void protocol_base::set_version(const message::version& value)
{
    channel_->set_version(value);
}
    
void protocol_base::stop(const code& ec)
{
    channel_->stop(ec);
}
    
bool protocol_base::stopped() const
{
    return channel_->stopped();
}

} // namespace network
} // namespace libbitcoin

