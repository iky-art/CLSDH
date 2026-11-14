# 📋 CLSDH Usage Guide on Termux (English)

> Detailed guide to run every CLSDH tool in Termux environment.

---

## 🔗 Link Checking

```bash
./clsdh link-check https://example.com http://example.org
./clsdh link-check https://site.com --concurrency 20 --timeout 10
./clsdh link-check https://site.com -o ~/link-result.txt
```

## 🔌 Port Checking

```bash
./clsdh tcp-port google.com 443
./clsdh tcp-port localhost 8080 5000
./clsdh udp-port 8.8.8.8 53
```

## 🖥️ System Monitors

```bash
./clsdh cpu-monitor      # Press Ctrl+C to stop
./clsdh mem-monitor      # Press Ctrl+C to stop
./clsdh disk-monitor /   # Press Ctrl+C to stop
./clsdh net-stats        # Press Ctrl+C to stop
./clsdh load-avg         # Press Ctrl+C to stop
```

## 🌐 Network & DNS

```bash
./clsdh ping google.com 4
./clsdh dns-lookup google.com
./clsdh reverse-dns 8.8.8.8
./clsdh http-headers https://example.com
./clsdh port-scan localhost 1 100
```

## 🔐 Security & SSL

```bash
./clsdh ssl-cert google.com 443
./clsdh banner-grab localhost 22
./clsdh smtp-test mail.com 25
```

## 🔧 Utilities

```bash
./clsdh md5 "clsdh"
./clsdh sha256 "clsdh"
./clsdh base64-enc "halo"
./clsdh base64-dec "aGFsbw=="
./clsdh uuid
./clsdh password-gen 16
./clsdh url-encode "clsdh v2"
./clsdh url-decode "clsdh%20v2"
```

## 💾 File & System

```bash
./clsdh file-checksum ~/file.txt
./clsdh line-count ~/log.txt
./clsdh file-watch ~/config.ini
./clsdh uptime
./clsdh hostname
./clsdh ip-addr
./clsdh free-ram
./clsdh disk-usage
```

---

## 💡 Termux-Specific Tips

1. **Use Termux:Widget** to add CLSDH shortcut to Android home screen.
2. **Save results to `~/`** (home directory) for easy access from file manager.
3. **Use `termux-wake-lock`** if you want monitors to run for a long time without sleep.

---

> 🇬🇧 English documentation. Indonesian version available at `termux/usage-id.md`.
