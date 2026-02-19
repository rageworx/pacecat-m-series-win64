#ifndef __PACECATGLOBAL_H__
#define __PACECATGLOBAL_H__

#include <set>
#include <vector>
#include <cmath>
#include <deque>
#include <iostream>
#include <string>
#include <pacecatprotocol.h>

#define getbit(x,y)   ((x) >> (y)&1)
#define setbit(x,y) x|=(1<<y)         /// Position X at the Y-th position 1
#define clrbit(x,y) x&=~(1<<y)        /// Clear the Y-th bit of X to 0.
#ifndef M_PI
    #define M_PI 3.14159265358979323846
#endif /// of M_PI

#ifdef _WIN32
    typedef uint32_t    in_addr_t;
    typedef uint16_t    in_port_y;
#endif

// Custom struct? -> Command Record
struct CmdRecord
{
    char cmd[1024];         /// instruction | command
    int len;                /// Instruction length
    uint16_t sn;            /// Random code? SN ?
    uint32_t ts;            /// Timestamp
    uint16_t sign;          /// Return Protocol
    uint32_t num;           /// Number of resends
    int mode;
};

namespace BaseAPI 
{
    std::string stringfilter(char *str,int num);
	bool        judgepcIPAddrIsValid(const char *pcIPAddr);
	bool        mask_check(const char *mask);
	bool        mac_check(const char *mac);
	bool        checkAndMerge(int type, char*ip, char*mask, char*gateway, int port, char*result);
    std::string bin_to_hex_fast(const uint8_t *data, size_t length, bool uppercase);
    uint32_t    stm32crc(uint32_t* ptr, uint32_t len);
    bool        isBitSet(uint8_t num, int n);
}

namespace SystemAPI
{
    int         open_socket_port(int port,bool isRepeat);
    int         open_socket_port();
    int         closefd(int __fd,bool isSocket);
    int         getLastError();
    uint64_t    GetTimeStamp(bool isTimeStamp_M);
    uint64_t    getCurrentNanoseconds();
    std::string getCurrentTime();
    in_addr_t   get_interface_ip(const char *ifname);
}

namespace CommunicationAPI 
{
	void    send_cmd_udp(int fd_udp, const char* dev_ip, int dev_port, \
                         int cmd, int sn, int len, const void* snd_buf);
	bool    udp_talk_pack(int fd_udp, const char * lidar_ip, int lidar_port, \
                          int send_len, const char * send_buf, int mode, \
                          int & recv_len, char * recv_buf, \
                          int delay=3, int delaynum=10000);
}

namespace AlgorithmAPI
{
    double  calculateDistance(const LidarCloudPointData& pointA, \
                              const LidarCloudPointData& pointB);
    bool    checkWindowValid2(std::vector<LidarCloudPointData> &scan, \
                              size_t idx, size_t window, double max_distance);
    int     OutlierFilter(std::vector<LidarCloudPointData> &scan_in, \
                          const ShadowsFilterParam &param, \
                          std::vector<double> &tmp_ang ,PointFilterParam &pfp);

    double  getAngleWithViewpoint(float r1, float r2, double included_angle);
    int     ShadowsFilter(std::vector<LidarCloudPointData> &scan_in, \
                          std::vector<double> &ang_in, \
                          const ShadowsFilterParam& param, \
                          std::vector<double> &tmp_ang);
    void    setMatrixRotateParam(MatrixRotate mr,MatrixRotate_2 &mr_2);
}

#endif /// of __PACECATGLOBAL_H__
