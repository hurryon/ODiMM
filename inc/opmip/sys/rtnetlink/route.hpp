//=============================================================================
// Brief   : RT Netlink Route Message
// Authors : Bruno Santos <bsantos@av.it.pt>
// ----------------------------------------------------------------------------
// OPMIP - Open Proxy Mobile IP
//
// Copyright (C) 2010 Universidade de Aveiro
// Copyrigth (C) 2010 Instituto de Telecomunicações - Pólo de Aveiro
//
// This software is distributed under a license. The full license
// agreement can be found in the file LICENSE in this distribution.
// This software may not be copied, modified, sold or distributed
// other than expressed in the named license agreement.
//
// This software is distributed without any warranty.
//=============================================================================

#ifndef OPMIP_SYS_RTNETLINK_ROUTE__HPP_
#define OPMIP_SYS_RTNETLINK_ROUTE__HPP_

///////////////////////////////////////////////////////////////////////////////
#include <opmip/base.hpp>

///////////////////////////////////////////////////////////////////////////////
namespace opmip { namespace sys { namespace rtnl {

///////////////////////////////////////////////////////////////////////////////
class route {
public:
	enum m_type {
		m_begin = 24,

		m_new = m_begin,
		m_del,
		m_get,

		m_end
	};

	enum table {
		table_unspecified = 0,

		table_compat  = 252,
		table_default = 253,
		table_main    = 254,
		table_local   = 255,
	};

	/***
	 * Values of protocol >= proto_static are not interpreted by kernel,
	 * they are just passed from user and back as is. It will be used by
	 * hypothetical multiple routing daemons. Note that protocol values
	 * should be standardized in order to avoid conflicts.
	 */
	enum proto {
		proto_unspecified = 0, ///Route installed by ICMP redirects, not used by current IPv4
		proto_kernel,          ///Route installed by kernel
		proto_boot,            ///Route installed during boot
		proto_static,          ///Route installed by administrator

		proto_gated,    ///Apparently, GateD
		proto_ra,       ///RDISC/ND router advertisements
		proto_mrt,      ///Merit MRT
		proto_zebra,    ///Zebra
		proto_bird,     ///BIRD
		proto_dnrouted, ///DECnet routing daemon
		proto_xorp,     ///XORP
		proto_ntk,      ///Netsukuku
		proto_dhcp,     ///DHCP client
	};

	enum scope {
		scope_universe = 0,

		scope_site    = 200,
		scope_link    = 253,
		scope_host    = 254,
		scope_nowhere = 255,
	};

	enum r_type {
		r_unspecified,
		r_unicast,              ///Gateway or direct route
		r_local,                ///Accept locally
		r_broadcast,            ///Accept locally as broadcast, send as broadcast
		r_anycast,              ///Accept locally as broadcast, but send as unicast
		r_multicast,            ///Multicast route
		r_blackhole,            ///Drop
		r_unreachable,          ///Destination is unreachable
		r_prohibit,             ///Administratively prohibited
		r_throw,                ///Continue lookup in another table
		r_nat,                  ///Translate this address
		r_xresolve,             ///Use external resolver
	};

	enum flags {
		notify   = 0x100, ///Notify user of route change
		cloned   = 0x200, ///This route is cloned
		equalize = 0x400, ///Multipath equalizer: NI
		prefix   = 0x800, ///Prefix addresses
	};

	enum attr_type {
		attr_begin = 1,
		attr_destination = attr_begin,
		attr_source,
		attr_input_device,
		attr_output_device,
		attr_gateway,
		attr_priority,
		attr_prefered_source,
		//imcomplete
		attr_end
	};

public:
	route()
		: family(0), dst_len(0), src_len(0), tos(0), table(0), protocol(0),
		  scope(0), type(0), flags(0)
	{ }

public:
	uchar family;
	uchar dst_len;
	uchar src_len;
	uchar tos;

	uchar table;    ///Routing table id
	uchar protocol; ///Routing protocol
	uchar scope;    ///Distance scope
	uchar type;

	uint  flags;
};

///////////////////////////////////////////////////////////////////////////////
} /* namespace rtnl */ } /* namespace sys */ } /* namespace opmip */

// EOF ////////////////////////////////////////////////////////////////////////
#endif /* OPMIP_SYS_RTNETLINK_ROUTE__HPP_ */
