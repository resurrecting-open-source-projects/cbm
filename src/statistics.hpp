#ifndef CBM_STATISTICS_H
#define CBM_STATISTICS_H

#include <list>
#include <string>
#include <sys/time.h>

namespace statistics {
    
struct Statistics {
    struct timeval timestamp;
    unsigned long long rx_bytes, rx_packets, rx_errs, rx_drop, rx_fifo,
		       rx_frame, rx_compressed, rx_multicast,
		       tx_bytes, tx_packets, tx_errs, tx_drop, tx_fifo,
		       tx_frame, tx_compressed, tx_multicast;
};

class Interface {
    public:
	Interface(const std::string& name);

	const std::string& getName() const;

	void setUpdated(bool updated);
	bool getUpdated() const;

	void update(const Statistics& statistics);
	
	double getReceiveSpeed() const;
	double getTransmitSpeed() const;

    private:
	std::string name_;
	bool updated_;
	Statistics statistics_[2];
	double receiveSpeed_, transmitSpeed_;
};

class Reader {
    public:
	void update();
	
	typedef std::list<Interface> Interfaces;
	const Interfaces& getInterfaces() const;
	
    private:
	Interfaces interfaces_;
};

} // namespace statistics

#endif
