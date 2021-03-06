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
#ifndef LIBBITCOIN_NETWORK_CONNECTOR_HPP
#define LIBBITCOIN_NETWORK_CONNECTOR_HPP

#include <functional>
#include <memory>
#include <string>
#include <bitcoin/bitcoin/config/authority.hpp>
#include <bitcoin/bitcoin/config/endpoint.hpp>
#include <bitcoin/bitcoin/define.hpp>
#include <bitcoin/bitcoin/error.hpp>
#include <bitcoin/bitcoin/network/asio.hpp>
#include <bitcoin/bitcoin/network/channel.hpp>
#include <bitcoin/bitcoin/network/network_settings.hpp>
#include <bitcoin/bitcoin/utility/threadpool.hpp>

namespace libbitcoin {
namespace network {

class BC_API connector
  : public std::enable_shared_from_this<connector>, track<connector>
{
public:
    typedef std::shared_ptr<connector> ptr;
    typedef std::function<void(const code&, channel::ptr)> connect_handler;

    /// Construct the connector.
    connector(threadpool& pool, const settings& settings);

    /// This class is not copyable.
    connector(const connector&) = delete;
    void operator=(const connector&) = delete;

    /// Cancel all outstanding connection attempt.
    void cancel();

    /// Try to connect to the endpoint.
    void connect(const config::endpoint& endpoint,
        connect_handler handler);

    /// Try to connect to the authority.
    void connect(const config::authority& authority,
        connect_handler handler);

    /// Try to connect to host:port.
    void connect(const std::string& hostname, uint16_t port,
        connect_handler handler);

private:
    void handle_resolve(const boost_code& ec, asio::iterator iterator,
        connect_handler handler);
    void handle_timer(const code& ec, asio::socket_ptr socket,
        connect_handler handler);
    void handle_connect(const boost_code& ec, asio::iterator iterator,
        asio::socket_ptr socket, deadline::ptr timer, connect_handler handler);

    threadpool& pool_;
    const settings& settings_;
    std::shared_ptr<asio::resolver> resolver_;
};

} // namespace network
} // namespace libbitcoin

#endif
