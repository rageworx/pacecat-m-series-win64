#ifndef __PACECATPLAYBACK_H__
#define __PACECATPLAYBACK_H__
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

#ifndef _WIN32
    #include <sys/mman.h>
    #include <sys/stat.h>
    #include <arpa/inet.h>
    #include <netinet/ip.h>
    #include <netinet/udp.h>
#else
    // minGW-W64 users are need 'mman'.
    // see : https://packages.msys2.org/base/mingw-w64-mman-win32
    #include <winsock2.h>
    #include <sys/stat.h>
    #include <sys/mman.h>
#endif

#include <time.h>
#include <pthread.h>
#include <signal.h>

// ======================
// PCAP file format definition
// ======================
typedef struct pcap_file_header 
{
    uint32_t magic_number;      /// 0xa1b2c3d4
    uint16_t version_major;     /// 2
    uint16_t version_minor;     /// 4
    int32_t  thiszone;          /// GMT to local correction
    uint32_t sigfigs;           /// accuracy of timestamps
    uint32_t snaplen;           /// max length of captured packets
    uint32_t linktype;          /// data link type (1 = Ethernet)
} pcap_file_header_t;

typedef struct pcap_packet_header 
{
    uint32_t ts_sec;            /// timestamp seconds
    uint32_t ts_usec;           /// timestamp microseconds
    uint32_t incl_len;          /// number of octets of packet saved in file
    uint32_t orig_len;          /// actual length of packet
} pcap_packet_header_t;

// ======================
// Configuration parameters
// ======================
#define MAX_PACKET_SIZE   1500                  /// Maximum UDP packet size
#define MEMORY_MAP_SIZE   (1024 * 1024 * 1024)  /// 1GB memory-mapped block
#define STATS_INTERVAL    5                     /// Statistical information printing interval (seconds)
#define MAX_PROTOCOLS     10                    /// Maximum supported protocol types

// =====================================
// Radar Protocol Type Definition
// =====================================
typedef enum 
{
    LIDAR_PROTO_UNKNOWN = 0,
    LIDAR_PROTO_TYPE_M_SERIES
} LidarProtocolType;

// =====================================
// Protocol processing function pointer
// =====================================
typedef void (*ProtocolParser)(const uint8_t* data, size_t length, \
                               const pcap_packet_header_t* pcap_hdr, \
                               void* context);

// =====================================
// Protocol processor architecture
// =====================================
typedef struct 
{
    LidarProtocolType type;
    const char* name;
    ProtocolParser parser;
} ProtocolHandler;

// ======================
// Context parsing
// ======================
typedef struct 
{
    int     fd;                 /// file descriptor
    size_t  file_size;          /// Total file size
    size_t  processed_size;     /// Processed size
    size_t  current_offset;     /// Current offset
    void*   mmap_ptr;           /// Memory-mapped pointers
    size_t  mmap_size;          /// Current mapping size
    size_t  last_mapped_offset; /// Starting offset of the last mapping
    
    // Statistical information
    uint64_t pointcloud_num;
    uint64_t imu_num;
    uint64_t heart_num;
    uint64_t bytes_processed;
    time_t last_stat_time;
    
    // Protocol processor
    ProtocolHandler handlers[MAX_PROTOCOLS];
    int handler_count;
    
    // Real-time print control
    volatile sig_atomic_t running;
} ParseContext;

// ======================
// Function declaration
// ======================
int     init_context(ParseContext* ctx, const char* filename);
void    destroy_context(ParseContext* ctx);
int     map_next_chunk(ParseContext* ctx);
int     parse_chunk(ParseContext* ctx);
long    get_page_size();

#endif /// of __PACECATPLAYBACK_H__
