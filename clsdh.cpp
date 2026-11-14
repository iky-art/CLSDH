// clsdh.cpp - CLSDH v2.0.0 Multi-Tool Suite (C++, dependency-free)
// Indo : Cek Link Sebelum Data Hilang
// Eng  : Check Links Before Data Loss
// Compile: g++ -std=c++11 -O2 -pthread clsdh.cpp -o clsdh
//
// Usage:
//   ./clsdh <tool> [args...]
//   ./clsdh list
//   ./clsdh link-check https://example.com

#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <mutex>
#include <chrono>
#include <atomic>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <cstring>
#include <cstdlib>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <fcntl.h>
#include <poll.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/statfs.h>
#include <sys/types.h>
#include <signal.h>

static const char* PROGRAM = "CLSDH";
static const char* VERSION = "2.0.0";
static const char* FULL_NAME_ID = "Cek Link Sebelum Data Hilang";
static const char* FULL_NAME_EN = "Check Links Before Data Loss";

static bool g_useColor = true;
static std::mutex g_coutMutex;
static std::atomic<bool> g_stopMonitor{false};

static const char* C_RESET  = "\033[0m";
static const char* C_GREEN  = "\033[32m";
static const char* C_RED    = "\033[31m";
static const char* C_YELLOW = "\033[33m";
static const char* C_CYAN   = "\033[36m";
static const char* C_BOLD   = "\033[1m";

static void applyColor(bool useColor) {
    if (!useColor) { C_RESET=C_GREEN=C_RED=C_YELLOW=C_CYAN=C_BOLD=""; }
}

static void handleSigInt(int) { g_stopMonitor = true; }

static std::string trim(const std::string& s) {
    size_t a = s.find_first_not_of(" \t\r\n");
    if (a == std::string::npos) return "";
    size_t b = s.find_last_not_of(" \t\r\n");
    return s.substr(a, b - a + 1);
}

static std::string nowTs() {
    auto now = std::chrono::system_clock::now();
    std::time_t t = std::chrono::system_clock::to_time_t(now);
    std::tm tm; localtime_r(&t, &tm);
    std::ostringstream os;
    os << std::setfill('0') << std::setw(2) << tm.tm_hour << ":"
       << std::setw(2) << tm.tm_min << ":" << std::setw(2) << tm.tm_sec;
    return os.str();
}

static void logLine(const std::string& s) {
    std::lock_guard<std::mutex> lock(g_coutMutex);
    std::cout << s << "\n";
    std::cout.flush();
}

static std::string execCmd(const std::string& cmd) {
    std::string result;
    FILE* pipe = popen(cmd.c_str(), "r");
    if (!pipe) return "";
    char buf[256];
    while (fgets(buf, sizeof(buf), pipe) != nullptr) result += buf;
    pclose(pipe);
    return result;
}

static void sleepMs(int ms) { std::this_thread::sleep_for(std::chrono::milliseconds(ms)); }

static void printBanner() {
    std::cout << C_CYAN << C_BOLD
              << " CCCCC   L      SSSSS   DDDDD   HH   HH \n"
              << "C         L      S      D   D   HH   HH \n"
              << "C         L      SSS    D   D   HHHHHHH \n"
              << "C         L           S  D   D   HH   HH \n"
              << " CCCCC   LLLLL   SSSSS   DDDDD   HH   HH \n"
              << C_RESET
              << "   " << C_BOLD << "CLSDH" << C_RESET << " v" << VERSION << "\n"
              << "   " << C_BOLD << "CLSDH" << C_RESET << " - " << FULL_NAME_ID << "\n"
              << "   " << C_BOLD << "CLSDH" << C_RESET << " - " << FULL_NAME_EN << "\n"
              << "   CLI • C++ • Real-time • Tanpa dependensi eksternal\n"
              << "\n";
}

static bool parseHostPort(const std::string& input, std::string& host, int& port) {
    size_t colon = input.rfind(':');
    if (colon == std::string::npos) return false;
    host = input.substr(0, colon);
    port = atoi(input.substr(colon+1).c_str());
    return port > 0 && port <= 65535;
}

static bool tcpConnect(const std::string& host, int port, int timeoutMs, int& sockfd) {
    struct addrinfo hints{}, *ai=nullptr;
    hints.ai_family = AF_UNSPEC; hints.ai_socktype = SOCK_STREAM;
    std::string p = std::to_string(port);
    if (getaddrinfo(host.c_str(), p.c_str(), &hints, &ai) != 0) return false;
    sockfd = -1;
    for (struct addrinfo* p=ai; p; p=p->ai_next) {
        sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
        if (sockfd < 0) continue;
        int flags = fcntl(sockfd, F_GETFL, 0); fcntl(sockfd, F_SETFL, flags|O_NONBLOCK);
        int rc = connect(sockfd, p->ai_addr, p->ai_addrlen);
        if (rc == 0) break;
        if (errno != EINPROGRESS) { close(sockfd); sockfd=-1; continue; }
        struct pollfd pfd; pfd.fd=sockfd; pfd.events=POLLOUT;
        int pres = poll(&pfd, 1, timeoutMs);
        if (pres > 0) {
            int err=0; socklen_t len=sizeof(err);
            getsockopt(sockfd, SOL_SOCKET, SO_ERROR, &err, &len);
            if (err==0) break;
        }
        close(sockfd); sockfd=-1;
    }
    freeaddrinfo(ai);
    return sockfd >= 0;
}

static bool udpConnect(const std::string& host, int port, int timeoutMs, int& sockfd) {
    struct addrinfo hints{}, *ai=nullptr;
    hints.ai_family = AF_UNSPEC; hints.ai_socktype = SOCK_DGRAM;
    std::string p = std::to_string(port);
    if (getaddrinfo(host.c_str(), p.c_str(), &hints, &ai) != 0) return false;
    sockfd = -1;
    for (struct addrinfo* p=ai; p; p=p->ai_next) {
        sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
        if (sockfd < 0) continue;
        struct timeval tv; tv.tv_sec = timeoutMs/1000; tv.tv_usec = (timeoutMs%1000)*1000;
        setsockopt(sockfd, SOL_SOCKET, SO_SNDTIMEO, &tv, sizeof(tv));
        setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv));
        if (connect(sockfd, p->ai_addr, p->ai_addrlen) == 0) break;
        close(sockfd); sockfd=-1;
    }
    freeaddrinfo(ai);
    return sockfd >= 0;
}

static void toolLinkCheck(const std::vector<std::string>& args) {
    if (args.empty()) { std::cerr << "Usage: clsdh link-check <url> [--concurrency N] [--timeout T]\n"; return; }
    std::vector<std::string> urls; int conc=30, timeout=10;
    for (size_t i=0;i<args.size();i++){
        if (args[i]=="--concurrency" && i+1<args.size()) conc=atoi(args[++i].c_str());
        else if (args[i]=="--timeout" && i+1<args.size()) timeout=atoi(args[++i].c_str());
        else urls.push_back(args[i]);
    }
    if (urls.empty()) { std::cerr << "No URLs.\n"; return; }
    printBanner();
    std::cout << C_BOLD<<"URLs:"<<C_RESET<<" "<<urls.size()
              <<"  "<<C_BOLD<<"Concurrency:"<<C_RESET<<" "<<conc
              <<"  "<<C_BOLD<<"Timeout:"<<C_RESET<<" "<<timeout<<"s\n";
    std::cout<<std::string(70,'-')<<"\n";
    size_t idx=0;
    while (idx<urls.size()) {
        std::vector<std::thread> ths;
        size_t end=std::min(idx+(size_t)conc, urls.size());
        for (size_t j=idx;j<end;j++) {
            ths.emplace_back([urls,j,timeout](){
                auto t0=std::chrono::steady_clock::now();
                std::string scheme="http",host,path; int port=80;
                std::string u=urls[j];
                size_t sep=u.find("://");
                if (sep!=std::string::npos){ scheme=u.substr(0,sep); u=u.substr(sep+3);}
                size_t slash=u.find('/');
                std::string hostPart=(slash==std::string::npos)?u:u.substr(0,slash);
                path=(slash==std::string::npos)?"/":u.substr(slash);
                size_t colon=hostPart.rfind(':');
                if (colon!=std::string::npos){ host=hostPart.substr(0,colon); port=atoi(hostPart.substr(colon+1).c_str()); }
                else { host=hostPart; port=(scheme=="https")?443:80; }
                int sfd=-1;
                if (!tcpConnect(host,port,timeout*1000,sfd)) {
                    logLine("["+nowTs()+"] "+C_RED+"[DOWN]"+C_RESET+" "+urls[j].substr(0,64)+" ERR connection failed");
                    return;
                }
                std::string req="HEAD "+path+" HTTP/1.1\r\nHost: "+host+"\r\nConnection: close\r\n\r\n";
                send(sfd, req.c_str(), req.size(), 0);
                char buf[2048]; std::string resp;
                struct pollfd pfd; pfd.fd=sfd; pfd.events=POLLIN;
                int pres=poll(&pfd,1,timeout*1000);
                if (pres>0){ ssize_t n=recv(sfd,buf,sizeof(buf)-1,0); if(n>0){buf[n]=0; resp=buf;} }
                close(sfd);
                auto t1=std::chrono::steady_clock::now();
                long ms=std::chrono::duration_cast<std::chrono::milliseconds>(t1-t0).count();
                size_t sp=resp.find(' ');
                if (sp!=std::string::npos && sp+1<resp.size()) {
                    std::string code=resp.substr(sp+1,3);
                    bool up=(code[0]=='2'||code[0]=='3');
                    logLine("["+nowTs()+"] "+(up?C_GREEN:C_RED)+"["+(up?"UP":"DOWN")+"]"+C_RESET+" "+urls[j].substr(0,64)+
                            " HTTP "+code+" ("+std::to_string(ms)+" ms)");
                } else {
                    logLine("["+nowTs()+"] "+C_RED+"[DOWN]"+C_RESET+" "+urls[j].substr(0,64)+" ERR no response ("+std::to_string(ms)+" ms)");
                }
            });
        }
        for(auto&t:ths) t.join();
        idx=end;
    }
    std::cout<<std::string(70,'-')<<"\n";
}

static void toolTcpPort(const std::vector<std::string>& args) {
    if (args.size()<2){std::cerr<<"Usage: clsdh tcp-port <host> <port> [timeoutMs]\n";return;}
    std::string host=args[0]; int port=atoi(args[1].c_str()); int tm= (args.size()>2)?atoi(args[2].c_str()):3000;
    printBanner();
    int sfd=-1; bool ok=tcpConnect(host,port,tm,sfd);
    if (sfd>=0) close(sfd);
    std::cout<<C_BOLD<<"TCP "<<host<<":"<<port<<C_RESET<<" -> "<<(ok?C_GREEN:C_RED)<<(ok?"OPEN":"CLOSED")<<C_RESET<<"\n";
}

static void toolUdpPort(const std::vector<std::string>& args) {
    if (args.size()<2){std::cerr<<"Usage: clsdh udp-port <host> <port> [timeoutMs]\n";return;}
    std::string host=args[0]; int port=atoi(args[1].c_str()); int tm= (args.size()>2)?atoi(args[2].c_str()):3000;
    printBanner();
    int sfd=-1; bool ok=udpConnect(host,port,tm,sfd);
    if (sfd>=0) close(sfd);
    std::cout<<C_BOLD<<"UDP "<<host<<":"<<port<<C_RESET<<" -> "<<(ok?C_GREEN:C_RED)<<(ok?"REACHABLE":"UNREACHABLE")<<C_RESET<<"\n";
}

static void toolPing(const std::vector<std::string>& args) {
    if (args.empty()){std::cerr<<"Usage: clsdh ping <host> [count]\n";return;}
    std::string host=args[0]; int count=(args.size()>1)?atoi(args[1].c_str()):4;
    printBanner();
    std::cout<<C_BOLD<<"PING "<<host<<C_RESET<<"\n";
    for(int i=0;i<count && !g_stopMonitor;i++){
        std::string cmd="ping -c 1 -W 2 "+host+" | grep -o 'time=[0-9.]*'";
        std::string r=execCmd(cmd);
        auto t0=std::chrono::steady_clock::now();
        std::string line=r;
        if (line.empty()) line="timeout";
        else { size_t p=line.find("time="); if(p!=std::string::npos) line=line.substr(p); }
        auto t1=std::chrono::steady_clock::now();
        long ms=std::chrono::duration_cast<std::chrono::milliseconds>(t1-t0).count();
        std::cout<<"["<<nowTs()<<"] "<<host<<" "<<line<<" ("<<ms<<" ms)\n";
        std::cout.flush();
        sleepMs(1000);
    }
}

static void toolDnsLookup(const std::vector<std::string>& args) {
    if (args.empty()){std::cerr<<"Usage: clsdh dns-lookup <domain>\n";return;}
    printBanner();
    struct addrinfo hints{}, *ai=nullptr;
    hints.ai_family=AF_UNSPEC;
    if(getaddrinfo(args[0].c_str(),NULL,&hints,&ai)!=0){std::cerr<<C_RED<<"DNS failed"<<C_RESET<<"\n";return;}
    for(struct addrinfo* p=ai;p;p=p->ai_next){
        char ip[INET6_ADDRSTRLEN];
        void* addr = (p->ai_family==AF_INET)?(void*)&((struct sockaddr_in*)p->ai_addr)->sin_addr:(void*)&((struct sockaddr_in6*)p->ai_addr)->sin6_addr;
        inet_ntop(p->ai_family,addr,ip,sizeof(ip));
        std::cout<<"["<<nowTs()<<"] "<<args[0]<<" -> "<<ip<<"\n";
    }
    freeaddrinfo(ai);
}

static void toolReverseDns(const std::vector<std::string>& args) {
    if (args.empty()){std::cerr<<"Usage: clsdh reverse-dns <ip>\n";return;}
    printBanner();
    struct sockaddr_in sa; sa.sin_family=AF_INET;
    inet_pton(AF_INET,args[0].c_str(),&sa.sin_addr);
    char hbuf[NI_MAXHOST];
    if(getnameinfo((struct sockaddr*)&sa,sizeof(sa),hbuf,sizeof(hbuf),NULL,0,NI_NAMEREQD)==0)
        std::cout<<"["<<nowTs()<<"] "<<args[0]<<" -> "<<hbuf<<"\n";
    else
        std::cout<<"["<<nowTs()<<"] "<<args[0]<<" -> "<<C_RED<<"no PTR record"<<C_RESET<<"\n";
}

static void toolHttpHeaders(const std::vector<std::string>& args) {
    if (args.empty()){std::cerr<<"Usage: clsdh http-headers <url>\n";return;}
    printBanner();
    std::string url=args[0];
    std::string scheme="http",host,path; int port=80;
    size_t sep=url.find("://");
    if(sep!=std::string::npos){scheme=url.substr(0,sep); url=url.substr(sep+3);}
    size_t slash=url.find('/'); std::string hostPart=(slash==std::string::npos)?url:url.substr(0,slash);
    path=(slash==std::string::npos)?"/":url.substr(slash);
    size_t colon=hostPart.rfind(':');
    if(colon!=std::string::npos){host=hostPart.substr(0,colon); port=atoi(hostPart.substr(colon+1).c_str());}
    else {host=hostPart; port=(scheme=="https")?443:80;}
    int sfd=-1;
    if(!tcpConnect(host,port,5000,sfd)){std::cerr<<C_RED<<"connect failed"<<C_RESET<<"\n";return;}
    std::string req="HEAD "+path+" HTTP/1.1\r\nHost: "+host+"\r\nConnection: close\r\n\r\n";
    send(sfd,req.c_str(),req.size(),0);
    char buf[4096]; std::string resp;
    struct pollfd pfd; pfd.fd=sfd; pfd.events=POLLIN;
    if(poll(&pfd,1,5000)>0){ ssize_t n=recv(sfd,buf,sizeof(buf)-1,0); if(n>0){buf[n]=0; resp=buf;} }
    close(sfd);
    std::cout<<resp<<"\n";
}

static void toolPortScan(const std::vector<std::string>& args) {
    if (args.empty()){std::cerr<<"Usage: clsdh port-scan <host> [startPort] [endPort]\n";return;}
    std::string host=args[0]; int start=(args.size()>1)?atoi(args[1].c_str()):1; int end=(args.size()>2)?atoi(args[2].c_str()):1000;
    printBanner();
    std::cout<<C_BOLD<<"Scanning "<<host<<" ports "<<start<<"-"<<end<<C_RESET<<"\n";
    for(int p=start;p<=end && !g_stopMonitor;p++){
        int sfd=-1;
        if(tcpConnect(host,p,300,sfd)){
            if(sfd>=0) close(sfd);
            std::cout<<"["<<nowTs()<<"] "<<C_GREEN<<"OPEN"<<C_RESET<<" "<<host<<":"<<p<<"\n";
        }
    }
}

static void toolNtpTime(const std::vector<std::string>& args) {
    std::string host = args.empty()?"pool.ntp.org":args[0];
    printBanner();
    int sfd=-1;
    if(!udpConnect(host,123,3000,sfd)){std::cerr<<C_RED<<"NTP connect failed"<<C_RESET<<"\n";return;}
    uint8_t packet[48]={0}; packet[0]=0x1b;
    send(sfd,(char*)packet,48,0);
    uint8_t resp[48]; struct pollfd pfd; pfd.fd=sfd; pfd.events=POLLIN;
    if(poll(&pfd,1,3000)>0){ recv(sfd,(char*)resp,48,0); }
    close(sfd);
    uint32_t intPart = ntohl(*(uint32_t*)(resp+40));
    std::time_t t = (std::time_t)(intPart - 2208988800ULL);
    std::tm tm; gmtime_r(&t,&tm);
    std::cout<<"["<<nowTs()<<"] NTP "<<host<<" -> ";
    std::cout<<std::setfill('0')<<std::setw(2)<<tm.tm_hour<<":"<<std::setw(2)<<tm.tm_min<<":"<<std::setw(2)<<tm.tm_sec<<" UTC\n";
}

static void toolSmtpTest(const std::vector<std::string>& args) {
    if (args.empty()){std::cerr<<"Usage: clsdh smtp-test <host> [port]\n";return;}
    std::string host=args[0]; int port=(args.size()>1)?atoi(args[1].c_str()):25;
    printBanner();
    int sfd=-1;
    if(!tcpConnect(host,port,5000,sfd)){std::cout<<C_RED<<"SMTP "<<host<<":"<<port<<" DOWN"<<C_RESET<<"\n";return;}
    char buf[512]; recv(sfd,buf,sizeof(buf)-1,0);
    std::cout<<C_GREEN<<"SMTP "<<host<<":"<<port<<" UP"<<C_RESET<<" | Banner: "<<trim(std::string(buf))<<"\n";
    close(sfd);
}

static void toolHttpPost(const std::vector<std::string>& args) {
    if (args.empty()){std::cerr<<"Usage: clsdh http-post <url> [data]\n";return;}
    std::string url=args[0], data=(args.size()>1)?args[1]:"";
    printBanner();
    std::string scheme="http",host,path; int port=80;
    size_t sep=url.find("://");
    if(sep!=std::string::npos){scheme=url.substr(0,sep); url=url.substr(sep+3);}
    size_t slash=url.find('/'); std::string hostPart=(slash==std::string::npos)?url:url.substr(0,slash);
    path=(slash==std::string::npos)?"/":url.substr(slash);
    size_t colon=hostPart.rfind(':');
    if(colon!=std::string::npos){host=hostPart.substr(0,colon); port=atoi(hostPart.substr(colon+1).c_str());}
    else {host=hostPart; port=(scheme=="https")?443:80;}
    int sfd=-1;
    if(!tcpConnect(host,port,5000,sfd)){std::cerr<<C_RED<<"connect failed"<<C_RESET<<"\n";return;}
    std::string req="POST "+path+" HTTP/1.1\r\nHost: "+host+"\r\nContent-Length: "+std::to_string(data.size())+"\r\nConnection: close\r\n\r\n"+data;
    send(sfd,req.c_str(),req.size(),0);
    char buf[4096]; std::string resp;
    struct pollfd pfd; pfd.fd=sfd; pfd.events=POLLIN;
    if(poll(&pfd,1,5000)>0){ ssize_t n=recv(sfd,buf,sizeof(buf)-1,0); if(n>0){buf[n]=0; resp=buf;} }
    close(sfd);
    size_t sp=resp.find(' ');
    if(sp!=std::string::npos) std::cout<<"HTTP "<<resp.substr(sp+1,3)<<"\n";
    else std::cout<<resp<<"\n";
}

static std::string readProcLine(const std::string& file, const std::string& key) {
    std::ifstream in(file); std::string line;
    while(std::getline(in,line)){
        if(line.rfind(key,0)==0){ size_t c=line.find(':'); if(c!=std::string::npos) return trim(line.substr(c+1)); }
    }
    return "";
}

static void toolCpuMonitor(const std::vector<std::string>&) {
    printBanner(); signal(SIGINT, handleSigInt);
    std::cout<<C_BOLD<<"Real-time CPU Monitor (Ctrl+C to stop)"<<C_RESET<<"\n";
    while(!g_stopMonitor){
        std::string cpuLine=readProcLine("/proc/stat","cpu");
        std::istringstream iss(cpuLine); std::string label; long u,n,s,i;
        iss>>label>>u>>n>>s>>i;
        long total1=u+n+s+i, idle1=i; sleepMs(1000);
        cpuLine=readProcLine("/proc/stat","cpu"); iss.clear(); iss.str(cpuLine); iss>>label>>u>>n>>s>>i;
        long total2=u+n+s+i, idle2=i;
        double usage = total2>total1 ? 100.0 * (1 - (double)(idle2-idle1)/(double)(total2-total1)) : 0;
        std::cout<<"["<<nowTs()<<"] CPU: "<<std::fixed<<std::setprecision(1)<<usage<<"%\n";
        std::cout.flush();
    }
}

static void toolMemMonitor(const std::vector<std::string>&) {
    printBanner(); signal(SIGINT, handleSigInt);
    std::cout<<C_BOLD<<"Real-time Memory Monitor (Ctrl+C to stop)"<<C_RESET<<"\n";
    while(!g_stopMonitor){
        long total=0, avail=0, free=0;
        std::ifstream in("/proc/meminfo"); std::string line,k; long v;
        while(in>>k>>v){
            if(k=="MemTotal:") total=v;
            else if(k=="MemAvailable:") avail=v;
            else if(k=="MemFree:") free=v;
        }
        double usedPct = total>0 ? 100.0*(total-avail)/total : 0;
        std::cout<<"["<<nowTs()<<"] RAM: "<<std::fixed<<std::setprecision(1)<<usedPct<<"%  "
                 <<avail/1024<<"MB avail / "<<total/1024<<"MB total\n";
        std::cout.flush(); sleepMs(2000);
    }
}

static void toolDiskMonitor(const std::vector<std::string>& args) {
    std::string path = args.empty()?"/":args[0];
    printBanner(); signal(SIGINT, handleSigInt);
    std::cout<<C_BOLD<<"Real-time Disk Monitor: "<<path<<" (Ctrl+C to stop)"<<C_RESET<<"\n";
    while(!g_stopMonitor){
        struct statfs st;
        if(statfs(path.c_str(),&st)==0){
            uint64_t total = st.f_blocks*st.f_frsize;
            uint64_t free = st.f_bfree*st.f_frsize;
            uint64_t used = total-free;
            double pct = total>0 ? 100.0*used/total : 0;
            std::cout<<"["<<nowTs()<<"] Disk "<<path<<": "<<std::fixed<<std::setprecision(1)<<pct<<"%  "
                     <<used/(1024*1024)<<"MB used / "<<total/(1024*1024)<<"MB total\n";
        }
        std::cout.flush(); sleepMs(2000);
    }
}

static void toolUptime(const std::vector<std::string>&) {
    printBanner();
    std::ifstream in("/proc/uptime"); double up; in>>up;
    int sec=(int)up, h=sec/3600, m=(sec%3600)/60, s=sec%60;
    std::cout<<"["<<nowTs()<<"] Uptime: "<<h<<"h "<<m<<"m "<<s<<"s\n";
}

static void toolLoadAvg(const std::vector<std::string>&) {
    printBanner(); signal(SIGINT, handleSigInt);
    std::cout<<C_BOLD<<"Real-time Load Average (Ctrl+C to stop)"<<C_RESET<<"\n";
    while(!g_stopMonitor){
        double a[3]; std::ifstream in("/proc/loadavg");
        in>>a[0]>>a[1]>>a[2];
        std::cout<<"["<<nowTs()<<"] Load: "<<a[0]<<" "<<a[1]<<" "<<a[2]<<"\n";
        std::cout.flush(); sleepMs(1000);
    }
}

static void toolProcList(const std::vector<std::string>& args) {
    printBanner();
    int limit = args.empty()?20:atoi(args[0].c_str());
    std::cout<<C_BOLD<<"Top processes (first "<<limit<<"):"<<C_RESET<<"\n";
    std::string r=execCmd("ps -eo pid,ppid,user,pcpu,pmem,comm --sort=-pcpu | head -n "+std::to_string(limit+1));
    std::cout<<r<<"\n";
}

static void toolProcWatch(const std::vector<std::string>& args) {
    std::string name = args.empty()?"":args[0];
    printBanner(); signal(SIGINT, handleSigInt);
    std::cout<<C_BOLD<<"Watching process: "<<(name.empty()?"all":name)<<" (Ctrl+C to stop)"<<C_RESET<<"\n";
    while(!g_stopMonitor){
        std::string cmd = name.empty()?"ps -eo pid,comm --sort=-pcpu | head -n 15":
                        "ps -eo pid,comm | grep "+name+" | head -n 15";
        std::cout<<"\033[2J\033[H";
        printBanner();
        std::cout<<execCmd(cmd)<<"\n";
        std::cout.flush(); sleepMs(2000);
    }
}

static void toolNetStats(const std::vector<std::string>&) {
    printBanner(); signal(SIGINT, handleSigInt);
    std::cout<<C_BOLD<<"Real-time Network Stats (Ctrl+C to stop)"<<C_RESET<<"\n";
    auto readNet=[](const std::string& f)->uint64_t{
        std::ifstream in(f); std::string line; uint64_t tot=0;
        while(std::getline(in,line)){
            if(line.find(':')!=std::string::npos){
                std::istringstream iss(line); std::string iface; iss>>iface;
                if(iface=="lo:") continue;
                uint64_t rx,tx; iss>>rx; for(int i=0;i<7;i++){uint64_t x;iss>>x;}
                iss>>tx; tot+=rx+tx;
            }
        }
        return tot;
    };
    uint64_t prev=readNet("/proc/net/dev");
    while(!g_stopMonitor){
        sleepMs(1000);
        uint64_t cur=readNet("/proc/net/dev");
        double kbps=(cur-prev)/1024.0;
        std::cout<<"["<<nowTs()<<"] Net: "<<std::fixed<<std::setprecision(1)<<kbps<<" KB/s\n";
        prev=cur; std::cout.flush();
    }
}

static void toolHostname(const std::vector<std::string>&) {
    printBanner();
    char h[256]; gethostname(h, sizeof(h));
    std::cout<<"["<<nowTs()<<"] Hostname: "<<h<<"\n";
}

static void toolKernel(const std::vector<std::string>&) {
    printBanner();
    std::cout<<execCmd("uname -a")<<"\n";
}

static void toolOsInfo(const std::vector<std::string>&) {
    printBanner();
    std::ifstream in("/etc/os-release"); std::string line;
    while(std::getline(in,line)){
        if(line.rfind("PRETTY_NAME=",0)==0) std::cout<<"["<<nowTs()<<"] OS: "<<line.substr(14)<<"\n";
        else if(line.rfind("VERSION_ID=",0)==0) std::cout<<"["<<nowTs()<<"] Version: "<<line.substr(11)<<"\n";
    }
}

static void toolIpAddr(const std::vector<std::string>&) {
    printBanner();
    std::cout<<execCmd("ip -brief addr 2>/dev/null || ifconfig 2>/dev/null | head -n 30")<<"\n";
}

static void toolRoute(const std::vector<std::string>&) {
    printBanner();
    std::cout<<execCmd("ip route 2>/dev/null || netstat -rn 2>/dev/null")<<"\n";
}

static void toolFileChecksum(const std::vector<std::string>& args) {
    if (args.empty()){std::cerr<<"Usage: clsdh file-checksum <file>\n";return;}
    printBanner();
    std::string cmd="sha256sum "+args[0];
    std::cout<<execCmd(cmd)<<"\n";
}

static void toolFileWatch(const std::vector<std::string>& args) {
    if (args.empty()){std::cerr<<"Usage: clsdh file-watch <file>\n";return;}
    printBanner(); signal(SIGINT, handleSigInt);
    std::cout<<C_BOLD<<"Watching file: "<<args[0]<<" (Ctrl+C to stop)"<<C_RESET<<"\n";
    struct stat st; stat(args[0].c_str(),&st);
    time_t lastMtime=st.st_mtime;
    while(!g_stopMonitor){
        stat(args[0].c_str(),&st);
        if(st.st_mtime!=lastMtime){
            lastMtime=st.st_mtime;
            std::cout<<"["<<nowTs()<<"] FILE CHANGED: "<<args[0]<<"\n";
            std::cout.flush();
        }
        sleepMs(1000);
    }
}

static void toolLineCount(const std::vector<std::string>& args) {
    if (args.empty()){std::cerr<<"Usage: clsdh line-count <file>\n";return;}
    printBanner();
    std::ifstream in(args[0]); std::string line; long c=0;
    while(std::getline(in,line)) c++;
    std::cout<<"["<<nowTs()<<"] "<<args[0]<<": "<<c<<" lines\n";
}

static void toolDateTime(const std::vector<std::string>&) {
    printBanner();
    std::cout<<"["<<nowTs()<<"] "<<execCmd("date")<<"\n";
}

static void toolCalendar(const std::vector<std::string>&) {
    printBanner();
    std::cout<<execCmd("cal")<<"\n";
}

static void toolBase64Enc(const std::vector<std::string>& args) {
    if (args.empty()){std::cerr<<"Usage: clsdh base64-enc <text>\n";return;}
    printBanner();
    const std::string b64="ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    std::string out; const std::string& s=args[0];
    for(size_t i=0;i<s.size();i+=3){
        uint32_t b=0; int len=0;
        for(int j=0;j<3;j++) if(i+j<s.size()){ b=(b<<8)|(unsigned char)s[i+j]; len++; }
        b<<=(3-len)*8;
        for(int j=4;j>0;j--){ out+=b64[(b>>(j-1)*6)&0x3F]; }
        if(len<3) out[out.size()-(3-len)]='=';
    }
    std::cout<<out<<"\n";
}

static void toolBase64Dec(const std::vector<std::string>& args) {
    if (args.empty()){std::cerr<<"Usage: clsdh base64-dec <text>\n";return;}
    printBanner();
    auto val=[](char c)->int{
        if(c>='A'&&c<='Z') return c-'A';
        if(c>='a'&&c<='z') return c-'a'+26;
        if(c>='0'&&c<='9') return c-'0'+52;
        if(c=='+') return 62; if(c=='/') return 63; return -1;
    };
    std::string out; const std::string& s=args[0];
    for(size_t i=0;i<s.size();i+=4){
        uint32_t b=0; int n=0;
        for(int j=0;j<4;j++){ if(i+j<s.size() && s[i+j]!='='){ b=(b<<6)|val(s[i+j]); n++; } }
        b<<=(4-n)*6;
        for(int j=0;j<n-1;j++) out+=(char)((b>>(2-j)*8)&0xFF);
    }
    std::cout<<out<<"\n";
}

static void toolMd5(const std::vector<std::string>& args) {
    if (args.empty()){std::cerr<<"Usage: clsdh md5 <text>\n";return;}
    printBanner();
    std::cout<<execCmd("echo -n '"+args[0]+"' | md5sum")<<"\n";
}

static void toolSha1(const std::vector<std::string>& args) {
    if (args.empty()){std::cerr<<"Usage: clsdh sha1 <text>\n";return;}
    printBanner();
    std::cout<<execCmd("echo -n '"+args[0]+"' | sha1sum")<<"\n";
}

static void toolSha256(const std::vector<std::string>& args) {
    if (args.empty()){std::cerr<<"Usage: clsdh sha256 <text>\n";return;}
    printBanner();
    std::cout<<execCmd("echo -n '"+args[0]+"' | sha256sum")<<"\n";
}

static void toolUuid(const std::vector<std::string>&) {
    printBanner();
    std::cout<<execCmd("cat /proc/sys/kernel/random/uuid")<<"\n";
}

static void toolPasswordGen(const std::vector<std::string>& args) {
    int len = args.empty()?16:atoi(args[0].c_str());
    printBanner();
    const std::string charset="abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!@#$%^&*";
    std::string pw; srand(time(NULL));
    for(int i=0;i<len;i++) pw+=charset[rand()%charset.size()];
    std::cout<<"["<<nowTs()<<"] Password: "<<pw<<"\n";
}

static void toolHttpGet(const std::vector<std::string>& args) {
    if (args.empty()){std::cerr<<"Usage: clsdh http-get <url>\n";return;}
    printBanner();
    std::string url=args[0];
    std::string scheme="http",host,path; int port=80;
    size_t sep=url.find("://");
    if(sep!=std::string::npos){scheme=url.substr(0,sep); url=url.substr(sep+3);}
    size_t slash=url.find('/'); std::string hostPart=(slash==std::string::npos)?url:url.substr(0,slash);
    path=(slash==std::string::npos)?"/":url.substr(slash);
    size_t colon=hostPart.rfind(':');
    if(colon!=std::string::npos){host=hostPart.substr(0,colon); port=atoi(hostPart.substr(colon+1).c_str());}
    else {host=hostPart; port=(scheme=="https")?443:80;}
    int sfd=-1;
    if(!tcpConnect(host,port,5000,sfd)){std::cerr<<C_RED<<"connect failed"<<C_RESET<<"\n";return;}
    std::string req="GET "+path+" HTTP/1.1\r\nHost: "+host+"\r\nConnection: close\r\n\r\n";
    send(sfd,req.c_str(),req.size(),0);
    char buf[4096]; std::string resp;
    struct pollfd pfd; pfd.fd=sfd; pfd.events=POLLIN;
    while(poll(&pfd,1,5000)>0){
        ssize_t n=recv(sfd,buf,sizeof(buf)-1,0);
        if(n<=0) break; buf[n]=0; resp+=buf;
    }
    close(sfd);
    size_t body=resp.find("\r\n\r\n");
    if(body!=std::string::npos) std::cout<<resp.substr(body+4)<<"\n";
    else std::cout<<resp<<"\n";
}

static void toolWhois(const std::vector<std::string>& args) {
    if (args.empty()){std::cerr<<"Usage: clsdh whois <domain>\n";return;}
    printBanner();
    std::cout<<execCmd("whois "+args[0]+" 2>/dev/null | head -n 40")<<"\n";
}

static void toolSslCert(const std::vector<std::string>& args) {
    if (args.empty()){std::cerr<<"Usage: clsdh ssl-cert <host> [port]\n";return;}
    std::string host=args[0]; int port=(args.size()>1)?atoi(args[1].c_str()):443;
    printBanner();
    std::cout<<execCmd("echo | openssl s_client -connect "+host+":"+std::to_string(port)+" 2>/dev/null | openssl x509 -noout -subject -dates -issuer 2>/dev/null")<<"\n";
}

static void toolBannerGrab(const std::vector<std::string>& args) {
    if (args.size()<2){std::cerr<<"Usage: clsdh banner-grab <host> <port>\n";return;}
    std::string host=args[0]; int port=atoi(args[1].c_str());
    printBanner();
    int sfd=-1;
    if(!tcpConnect(host,port,3000,sfd)){std::cerr<<C_RED<<"connect failed"<<C_RESET<<"\n";return;}
    std::string probe="HEAD / HTTP/1.1\r\nHost: "+host+"\r\nConnection: close\r\n\r\n";
    send(sfd,probe.c_str(),probe.size(),0);
    char buf[1024]; std::string resp;
    struct pollfd pfd; pfd.fd=sfd; pfd.events=POLLIN;
    if(poll(&pfd,1,3000)>0){ ssize_t n=recv(sfd,buf,sizeof(buf)-1,0); if(n>0){buf[n]=0; resp=buf;} }
    close(sfd);
    size_t end=resp.find("\r\n\r\n");
    if(end!=std::string::npos) std::cout<<resp.substr(0,end)<<"\n";
    else std::cout<<resp<<"\n";
}

static void toolProcessTree(const std::vector<std::string>&) {
    printBanner();
    std::cout<<execCmd("pstree -p 2>/dev/null || ps -ef --forest | head -n 40")<<"\n";
}

static void toolDiskUsage(const std::vector<std::string>&) {
    printBanner();
    std::cout<<execCmd("df -h")<<"\n";
}

static void toolUsersList(const std::vector<std::string>&) {
    printBanner();
    std::ifstream in("/etc/passwd"); std::string line;
    while(std::getline(in,line)){
        std::istringstream iss(line); std::string user, x, uid, gid, info, home, shell;
        std::getline(iss,user,':'); std::getline(iss,x,':'); std::getline(iss,uid,':');
        std::getline(iss,gid,':'); std::getline(iss,info,':'); std::getline(iss,home,':'); std::getline(iss,shell,':');
        std::cout<<user<<" (UID:"+uid+") shell: "<<shell<<"\n";
    }
}

static void toolUnixTimestamp(const std::vector<std::string>&) {
    printBanner();
    std::cout<<"["<<nowTs()<<"] Unix timestamp: "<<time(NULL)<<"\n";
}

static void toolUrlEncode(const std::vector<std::string>& args) {
    if (args.empty()){std::cerr<<"Usage: clsdh url-encode <text>\n";return;}
    printBanner();
    std::string out; const std::string& s=args[0];
    for(char c: s){
        if(isalnum((unsigned char)c)||c=='-'||c=='_'||c=='.'||c=='~') out+=c;
        else { char b[4]; snprintf(b,sizeof(b),"%%%02X",(unsigned char)c); out+=b; }
    }
    std::cout<<out<<"\n";
}

static void toolUrlDecode(const std::vector<std::string>& args) {
    if (args.empty()){std::cerr<<"Usage: clsdh url-decode <text>\n";return;}
    printBanner();
    std::string out; const std::string& s=args[0];
    for(size_t i=0;i<s.size();i++){
        if(s[i]=='%' && i+2<s.size()){
            char hex[3]={s[i+1],s[i+2],0}; out+=(char)strtol(hex,NULL,16); i+=2;
        } else if(s[i]=='+') out+=' ';
        else out+=s[i];
    }
    std::cout<<out<<"\n";
}

static void toolCrontabList(const std::vector<std::string>&) {
    printBanner();
    std::cout<<execCmd("crontab -l 2>/dev/null || echo 'no crontab'")<<"\n";
}

static void toolTopCmd(const std::vector<std::string>& args) {
    int n = args.empty()?10:atoi(args[0].c_str());
    printBanner();
    std::cout<<execCmd("ps -eo pid,pcpu,pmem,comm --sort=-pcpu | head -n "+std::to_string(n+1))<<"\n";
}

static void toolFreeRam(const std::vector<std::string>&) {
    printBanner();
    std::cout<<execCmd("free -h")<<"\n";
}

static void printHelp() {
    printBanner();
    std::cout<<C_BOLD<<"Available tools:"<<C_RESET<<"\n";
    std::cout<<"  1. link-check         - Real-time HTTP link checker\n";
    std::cout<<"  2. tcp-port           - TCP port check\n";
    std::cout<<"  3. udp-port           - UDP port check\n";
    std::cout<<"  4. ping               - Ping host\n";
    std::cout<<"  5. dns-lookup         - DNS resolution\n";
    std::cout<<"  6. reverse-dns        - Reverse DNS (PTR)\n";
    std::cout<<"  7. http-headers       - HTTP headers (HEAD)\n";
    std::cout<<"  8. port-scan          - Port scanner\n";
    std::cout<<"  9. ntp-time           - NTP time sync\n";
    std::cout<<" 10. smtp-test          - SMTP banner check\n";
    std::cout<<" 11. http-post          - HTTP POST request\n";
    std::cout<<" 12. cpu-monitor        - Real-time CPU monitor\n";
    std::cout<<" 13. mem-monitor        - Real-time memory monitor\n";
    std::cout<<" 14. disk-monitor       - Real-time disk monitor\n";
    std::cout<<" 15. uptime             - System uptime\n";
    std::cout<<" 16. load-avg           - Real-time load average\n";
    std::cout<<" 17. proc-list          - Top processes\n";
    std::cout<<" 18. proc-watch         - Watch process (real-time)\n";
    std::cout<<" 19. net-stats          - Real-time network I/O\n";
    std::cout<<" 20. hostname           - Hostname\n";
    std::cout<<" 21. kernel             - Kernel info\n";
    std::cout<<" 22. os-info            - OS info\n";
    std::cout<<" 23. ip-addr            - IP addresses\n";
    std::cout<<" 24. route              - Routing table\n";
    std::cout<<" 25. file-checksum      - SHA256 checksum\n";
    std::cout<<" 26. file-watch         - Watch file changes\n";
    std::cout<<" 27. line-count         - Count lines in file\n";
    std::cout<<" 28. date-time          - Current date/time\n";
    std::cout<<" 29. calendar           - Calendar\n";
    std::cout<<" 30. base64-enc         - Base64 encode\n";
    std::cout<<" 31. base64-dec         - Base64 decode\n";
    std::cout<<" 32. md5                - MD5 hash\n";
    std::cout<<" 33. sha1               - SHA1 hash\n";
    std::cout<<" 34. sha256             - SHA256 hash\n";
    std::cout<<" 35. uuid               - Generate UUID\n";
    std::cout<<" 36. password-gen       - Generate password\n";
    std::cout<<" 37. http-get           - HTTP GET request\n";
    std::cout<<" 38. whois              - WHOIS lookup\n";
    std::cout<<" 39. ssl-cert           - SSL certificate info\n";
    std::cout<<" 40. banner-grab        - Service banner grab\n";
    std::cout<<" 41. proc-tree          - Process tree\n";
    std::cout<<" 42. disk-usage         - Disk usage (df -h)\n";
    std::cout<<" 43. users-list         - List system users\n";
    std::cout<<" 44. unix-timestamp     - Unix timestamp\n";
    std::cout<<" 45. url-encode         - URL encode\n";
    std::cout<<" 46. url-decode         - URL decode\n";
    std::cout<<" 47. crontab-list       - List cron jobs\n";
    std::cout<<" 48. top-cmd            - Top CPU processes\n";
    std::cout<<" 49. free-ram           - Memory free/used\n";
    std::cout<<"\n"<<C_BOLD<<"Usage:"<<C_RESET<<" clsdh <tool> [args...]\n";
    std::cout<<"Example: clsdh link-check https://example.com\n";
    std::cout<<"         clsdh cpu-monitor\n";
    std::cout<<"         clsdh tcp-port example.com 80\n";
}

int main(int argc, char** argv) {
    if (argc < 2) { printHelp(); return 0; }

    std::string tool = argv[1];
    std::vector<std::string> args;
    for (int i=2;i<argc;i++) args.push_back(argv[i]);

    if (tool == "list" || tool == "--help" || tool == "-h" || tool == "help") { printHelp(); return 0; }
    if (tool == "-v" || tool == "--version") {
        std::cout<<PROGRAM<<" v"<<VERSION<<" - "<<FULL_NAME_ID<<" / "<<FULL_NAME_EN<<"\n";
        return 0;
    }

    static const struct { const char* name; void (*fn)(const std::vector<std::string>&); } tools[] = {
        {"link-check", toolLinkCheck},
        {"tcp-port", toolTcpPort},
        {"udp-port", toolUdpPort},
        {"ping", toolPing},
        {"dns-lookup", toolDnsLookup},
        {"reverse-dns", toolReverseDns},
        {"http-headers", toolHttpHeaders},
        {"port-scan", toolPortScan},
        {"ntp-time", toolNtpTime},
        {"smtp-test", toolSmtpTest},
        {"http-post", toolHttpPost},
        {"cpu-monitor", toolCpuMonitor},
        {"mem-monitor", toolMemMonitor},
        {"disk-monitor", toolDiskMonitor},
        {"uptime", toolUptime},
        {"load-avg", toolLoadAvg},
        {"proc-list", toolProcList},
        {"proc-watch", toolProcWatch},
        {"net-stats", toolNetStats},
        {"hostname", toolHostname},
        {"kernel", toolKernel},
        {"os-info", toolOsInfo},
        {"ip-addr", toolIpAddr},
        {"route", toolRoute},
        {"file-checksum", toolFileChecksum},
        {"file-watch", toolFileWatch},
        {"line-count", toolLineCount},
        {"date-time", toolDateTime},
        {"calendar", toolCalendar},
        {"base64-enc", toolBase64Enc},
        {"base64-dec", toolBase64Dec},
        {"md5", toolMd5},
        {"sha1", toolSha1},
        {"sha256", toolSha256},
        {"uuid", toolUuid},
        {"password-gen", toolPasswordGen},
        {"http-get", toolHttpGet},
        {"whois", toolWhois},
        {"ssl-cert", toolSslCert},
        {"banner-grab", toolBannerGrab},
        {"proc-tree", toolProcessTree},
        {"disk-usage", toolDiskUsage},
        {"users-list", toolUsersList},
        {"unix-timestamp", toolUnixTimestamp},
        {"url-encode", toolUrlEncode},
        {"url-decode", toolUrlDecode},
        {"crontab-list", toolCrontabList},
        {"top-cmd", toolTopCmd},
        {"free-ram", toolFreeRam},
    };

    for (auto& t : tools) {
        if (tool == t.name) { t.fn(args); return 0; }
    }

    std::cerr<<C_RED<<"Unknown tool: "<<tool<<C_RESET<<"\nRun 'clsdh list' for available tools.\n";
    return 1;
}
