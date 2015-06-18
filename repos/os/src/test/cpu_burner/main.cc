#include <base/printf.h>
#include <base/allocator_avl.h>
#include <nic_session/connection.h>
#include <nic/packet_allocator.h>

using namespace Genode;

int main()
{
	PINF("Starting CPU burner");
	try {
		Nic::Packet_allocator p(env()->heap());
		Nic::Connection nic(&p, 512 * 1024, 512 * 1024);
	} catch (...) { }
	while (1) ;

	return 0;
}
