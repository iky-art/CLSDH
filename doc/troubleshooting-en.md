# 🔧 CLSDH Troubleshooting (English)

> Guide to handling common issues when using CLSDH.

---

## ❓ Common Issues

### 1. "command not found: clsdh"
**Cause:** Binary not compiled or not in PATH.

**Solution:**
```bash
# Compile first
g++ -std=c++11 -O2 -pthread clsdh.cpp -o clsdh

# Run with full path
./clsdh -v
```

---

### 2. https:// links show DOWN/timeout
**Cause:** CLSDH uses raw TCP socket without OpenSSL/TLS.

**Solution:** Use for `http://` or check TCP/UDP ports only. For accurate HTTPS, libcurl support is needed.

```bash
# This will DOWN (no TLS)
./clsdh link-check https://google.com

# This will UP (plain HTTP)
./clsdh link-check http://example.com
```

---

### 3. DNS: Name or service not known
**Cause:** Domain cannot be resolved or no internet connection.

**Solution:**
```bash
# Check internet connection
./clsdh ping google.com

# Check DNS
./clsdh dns-lookup google.com
```

---

### 4. Permission denied on port scan
**Cause:** Ports below 1024 require root access.

**Solution:**
```bash
sudo ./clsdh port-scan localhost 1 100
```

---

### 5. Output too fast / unreadable
**Cause:** Real-time output appears very quickly.

**Solution:** Save to file for later reading:
```bash
./clsdh link-check https://site.com -o result.txt
cat result.txt
```

---

## 🛠️ Diagnostic Commands

If experiencing issues, run the following for diagnostics:

```bash
./clsdh -v
./clsdh hostname
./clsdh ip-addr
./clsdh ping google.com
./clsdh dns-lookup google.com
```

---

## 📞 Support

Still having issues? Contact via **Instagram DM**: https://instagram.com/iky-art

---

> 🇬🇧 English documentation. Indonesian version available at `troubleshooting-id.md`.
