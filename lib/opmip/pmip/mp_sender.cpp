//=============================================================================
// Brief   : Mobility Protocol Sender
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

#include <opmip/pmip/mp_sender.hpp>

///////////////////////////////////////////////////////////////////////////////
namespace opmip { namespace pmip {

///////////////////////////////////////////////////////////////////////////////
pbu_sender::pbu_sender(const proxy_binding_info& pbinfo)
	: _endpoint(pbinfo.address), _length(0)
{
	std::fill(_buffer, _buffer + sizeof(_buffer), 0);

	ip::mproto::pbu*    pbu = new(_buffer) ip::mproto::pbu;
	ip::mproto::option* opt;
	size_t              len = sizeof(ip::mproto::pbu);

	pbu->sequence(pbinfo.sequence);
	pbu->ack(true);
	pbu->proxy_reg(true);
	pbu->lifetime(pbinfo.lifetime / 4000);

	//
	// NAI Option
	//
	ip::mproto::option::nai* nai;

	opt = new(_buffer + len) ip::mproto::option(ip::mproto::option::nai(), pbinfo.id.length());
	nai = opt->get<ip::mproto::option::nai>();
	nai->subtype = 1;
	std::copy(pbinfo.id.begin(), pbinfo.id.end(), nai->id);
	len += ip::mproto::option::size(opt);

	//
	// Handoff Option
	//
	ip::mproto::option::handoff* hof;

	opt = new(_buffer + len) ip::mproto::option(ip::mproto::option::handoff());
	hof = opt->get<ip::mproto::option::handoff>();
	hof->indicator = pbinfo.handoff;
	len += ip::mproto::option::size(opt);

	//
	//	Access Type Technology
	//
	ip::mproto::option::att* att;

	opt = new(_buffer + len) ip::mproto::option(ip::mproto::option::att());
	att = opt->get<ip::mproto::option::att>();
	att->tech_type = pbinfo.link_type;
	len += ip::mproto::option::size(opt);

	_length = align_to<8>(len);
	pbu->init(ip::mproto::pbu::mh_type, _length);
}

///////////////////////////////////////////////////////////////////////////////
pba_sender::pba_sender(const proxy_binding_info& pbinfo)
	: _endpoint(pbinfo.address), _length(0)
{
	std::fill(_buffer, _buffer + sizeof(_buffer), 0);

	ip::mproto::pba*    pba = new(_buffer) ip::mproto::pba;
	ip::mproto::option* opt;
	size_t              len = sizeof(ip::mproto::pba);

	pba->status(pbinfo.status);
	pba->proxy_reg(true);
	pba->sequence(pbinfo.sequence);
	pba->lifetime(pbinfo.lifetime / 4000);

	//
	// NAI Option
	//
	ip::mproto::option::nai* nai;

	opt = new(_buffer + len) ip::mproto::option(ip::mproto::option::nai(), pbinfo.id.length());
	nai = opt->get<ip::mproto::option::nai>();
	nai->subtype = 1;
	std::copy(pbinfo.id.begin(), pbinfo.id.end(), nai->id);
	len += ip::mproto::option::size(opt);

	//
	// Handoff Option
	//
	ip::mproto::option::handoff* hof;

	opt = new(_buffer + len) ip::mproto::option(ip::mproto::option::handoff());
	hof = opt->get<ip::mproto::option::handoff>();
	hof->indicator = pbinfo.handoff;
	len += ip::mproto::option::size(opt);

	//
	//	Access Type Technology
	//
	ip::mproto::option::att* att;

	opt = new(_buffer + len) ip::mproto::option(ip::mproto::option::att());
	att = opt->get<ip::mproto::option::att>();
	att->tech_type = pbinfo.link_type;
	len += ip::mproto::option::size(opt);

	_length = align_to<8>(len);
	pba->init(ip::mproto::pba::mh_type, _length);
}

///////////////////////////////////////////////////////////////////////////////
} /* namespace pmip */ } /* namespace opmip */

// EOF ////////////////////////////////////////////////////////////////////////