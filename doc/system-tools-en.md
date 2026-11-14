# 🖥️ CLSDH System Tools Guide (English)

> Detailed explanation of all system monitoring tools in CLSDH.

---

## 📊 Real-time Monitors

### CPU Monitor
```bash
./clsdh cpu-monitor
```
Displays CPU usage percentage every second. Press **Ctrl+C** to stop.

### Memory Monitor
```bash
./clsdh mem-monitor
```
Displays RAM usage percentage, available memory, and total memory in MB.

### Disk Monitor
```bash
./clsdh disk-monitor /
```
Displays disk usage percentage, used space, and total space in MB.

### Network Stats
```bash
./clsdh net-stats
```
Displays network transfer speed (KB/s) in real-time.

### Load Average
```bash
./clsdh load-avg
```
Displays system load for 1, 5, and 15 minutes every second.

---

## 📁 System Information

| Tool | Function | Example |
|------|----------|---------|
| `hostname` | Hostname | `./clsdh hostname` |
| `kernel` | Kernel version | `./clsdh kernel` |
| `os-info` | OS information | `./clsdh os-info` |
| `ip-addr` | IP addresses | `./clsdh ip-addr` |
| `route` | Routing table | `./clsdh route` |
| `uptime` | System uptime | `./clsdh uptime` |
| `free-ram` | RAM free/used | `./clsdh free-ram` |
| `disk-usage` | Disk usage | `./clsdh disk-usage` |

---

## 🔧 Process Management

| Tool | Function | Example |
|------|----------|---------|
| `proc-list` | Top processes | `./clsdh proc-list 20` |
| `proc-watch` | Watch process | `./clsdh proc-watch nginx` |
| `proc-tree` | Process tree | `./clsdh proc-tree` |
| `top-cmd` | Top CPU | `./clsdh top-cmd 10` |
| `users-list` | System users | `./clsdh users-list` |
| `crontab-list` | Cron jobs | `./clsdh crontab-list` |

---

## ⏹️ Stopping Monitors

All monitor tools (cpu-monitor, mem-monitor, disk-monitor, net-stats, load-avg) can be stopped by pressing **Ctrl+C**.

---

> 🇬🇧 English documentation. Indonesian version available at `system-tools-id.md`.
