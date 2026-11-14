# 📚 CLSDH API Reference (English)

> Complete reference for all command line tools and arguments supported by CLSDH.

---

## 📋 General Format

```bash
./clsdh <tool> [arguments...]
```

---

## 🌐 Network Tools

| Tool | Arguments | Description | Example |
|------|-----------|-------------|---------|
| `link-check` | `<url>... [--concurrency N] [--timeout T]` | Real-time HTTP link checker | `./clsdh link-check https://a.com --concurrency 10` |
| `tcp-port` | `<host> <port> [timeoutMs]` | Check open TCP port | `./clsdh tcp-port google.com 443` |
| `udp-port` | `<host> <port> [timeoutMs]` | Check UDP reachable | `./clsdh udp-port 8.8.8.8 53` |
| `ping` | `<host> [count]` | Ping host | `./clsdh ping google.com 4` |
| `dns-lookup` | `<domain>` | DNS resolution to IP | `./clsdh dns-lookup google.com` |
| `reverse-dns` | `<ip>` | Reverse DNS (PTR record) | `./clsdh reverse-dns 8.8.8.8` |
| `http-headers` | `<url>` | View HTTP headers (HEAD) | `./clsdh http-headers https://site.com` |
| `port-scan` | `<host> [start] [end]` | Port scanner 1-1000 | `./clsdh port-scan host.com 1 100` |
| `ntp-time` | `[host]` | NTP time sync | `./clsdh ntp-time pool.ntp.org` |
| `smtp-test` | `<host> [port]` | Check SMTP banner | `./clsdh smtp-test mail.com 25` |
| `http-post` | `<url> [data]` | Send HTTP POST request | `./clsdh http-post https://api.com "data=1"` |
| `http-get` | `<url>` | HTTP GET request | `./clsdh http-get https://api.com` |
| `whois` | `<domain>` | WHOIS domain lookup | `./clsdh whois example.com` |
| `ssl-cert` | `<host> [port>` | SSL/TLS certificate info | `./clsdh ssl-cert google.com 443` |
| `banner-grab` | `<host> <port>` | Grab service banner | `./clsdh banner-grab host.com 22` |

---

## 🖥️ System Tools

| Tool | Arguments | Description | Example |
|------|-----------|-------------|---------|
| `cpu-monitor` | - | Real-time CPU monitor | `./clsdh cpu-monitor` |
| `mem-monitor` | - | Real-time memory monitor | `./clsdh mem-monitor` |
| `disk-monitor` | `[path]` | Real-time disk monitor | `./clsdh disk-monitor /` |
| `uptime` | - | System uptime | `./clsdh uptime` |
| `load-avg` | - | Real-time load average | `./clsdh load-avg` |
| `proc-list` | `[limit]` | Top processes list | `./clsdh proc-list 20` |
| `proc-watch` | `[name]` | Watch process | `./clsdh proc-watch nginx` |
| `net-stats` | - | Real-time network stats | `./clsdh net-stats` |
| `hostname` | - | Hostname | `./clsdh hostname` |
| `kernel` | - | Kernel info | `./clsdh kernel` |
| `os-info` | - | OS info | `./clsdh os-info` |
| `ip-addr` | - | IP addresses | `./clsdh ip-addr` |
| `route` | - | Routing table | `./clsdh route` |
| `proc-tree` | - | Process tree | `./clsdh proc-tree` |
| `disk-usage` | - | Disk usage | `./clsdh disk-usage` |
| `users-list` | - | System users list | `./clsdh users-list` |
| `free-ram` | - | Memory free/used | `./clsdh free-ram` |
| `top-cmd` | `[n]` | Top CPU processes | `./clsdh top-cmd 10` |

---

## 📁 File & Utilities

| Tool | Arguments | Description | Example |
|------|-----------|-------------|---------|
| `file-checksum` | `<file>` | SHA256 checksum | `./clsdh file-checksum file.txt` |
| `file-watch` | `<file>` | Watch file changes | `./clsdh file-watch config.ini` |
| `line-count` | `<file>` | Count lines in file | `./clsdh line-count log.txt` |
| `date-time` | - | Current date/time | `./clsdh date-time` |
| `calendar` | - | Calendar | `./clsdh calendar` |
| `unix-timestamp` | - | Unix timestamp | `./clsdh unix-timestamp` |
| `base64-enc` | `<text>` | Base64 encode | `./clsdh base64-enc halo` |
| `base64-dec` | `<text>` | Base64 decode | `./clsdh base64-dec aGFsbw==` |
| `md5` | `<text>` | MD5 hash | `./clsdh md5 "clsdh"` |
| `sha1` | `<text>` | SHA1 hash | `./clsdh sha1 "clsdh"` |
| `sha256` | `<text>` | SHA256 hash | `./clsdh sha256 "clsdh"` |
| `uuid` | - | Generate UUID | `./clsdh uuid` |
| `password-gen` | `[length]` | Generate password | `./clsdh password-gen 16` |
| `url-encode` | `<text>` | URL encode | `./clsdh url-encode "clsdh v2"` |
| `url-decode` | `<text>` | URL decode | `./clsdh url-decode clsdh%20v2` |
| `crontab-list` | - | List cron jobs | `./clsdh crontab-list` |

---

## 🔧 Global Options

| Option | Description |
|--------|-------------|
| `-v, --version` | Show version |
| `-h, --help` | Show help |
| `list` | List all tools |
| `upd, --update` | Auto-update to latest version |
| `--no-color` | Disable ANSI colors |

---

> 🇬🇧 English documentation. Indonesian version available at `api-reference-id.md`.
