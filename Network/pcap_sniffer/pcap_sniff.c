#include <pcap.h>
#include <hacking.h>

void pcap_fatal(const char *failed_in, const char *errbuf) {
    printf("Critical error in %s: %s\n", failed_in, errbuf);
    exit(1);
}

int main() {
    struct pcap_pkthdr header;
    const u_char *packet;
    char errbuf[PCAP_ERRBUF_SIZE];
    pcap_if_t *alldevs, *device;
    pcap_t *pcap_handle;

    if (pcap_findalldevs(&alldevs, errbuf) == -1) {
        pcap_fatal("pcap_findalldevs", errbuf);
    }

    if (alldevs == NULL) {
        pcap_fatal("No devices found", "");
    }
    device = alldevs;
    
    printf("Sniffing on device: %s\n", device->name);

    pcap_handle = pcap_open_live(device->name, 4096, 1, 0, errbuf);
    if (pcap_handle == NULL) {
        pcap_fatal("pcap_open_live", errbuf);
    }

    for (int i = 0; i < 3; i++) {
        packet = pcap_next(pcap_handle, &header);
        if (packet != NULL) {
            printf("Received package size of %d bytes\n", header.len);
            dump(packet, header.len);
        } else {
            printf("No packet captured.\n");
        }
    }

    pcap_freealldevs(alldevs);
    pcap_close(pcap_handle);

    return 0;
}
