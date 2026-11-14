# 🎯 Getting Started with CLSDH (English)

> Quick start guide for beginners to use CLSDH effectively.

---

## 📖 What is CLSDH?

**CLSDH** stands for **"Check Links Before Data Loss"** (English) / **"Cek Link Sebelum Data Hilang"** (Indonesian). A CLI multi-tool written in C++ that lets you check links, monitor systems, and run network diagnostics in real-time — all in a single binary.

---

## 🚀 First Installation

### 1. Clone Repository
```bash
git clone https://github.com/iky-art/CLSDH.git
cd CLSDH
```

### 2. Compile
```bash
g++ -std=c++11 -O2 -pthread clsdh.cpp -o clsdh
```

### 3. Verify
```bash
./clsdh -v
```
**Expected Output:**
```
CLSDH v2.0.0 - Cek Link Sebelum Data Hilang / Check Links Before Data Loss
```

---

## ▶️ Basic Usage

CLSDH follows this command pattern:

```bash
./clsdh <tool_name> [arguments...]
```

### Example Link Check
```bash
./clsdh link-check https://example.com http://example.org
```

### Example Port Check
```bash
./clsdh tcp-port google.com 443
```

### List All Tools
```bash
./clsdh list
```

---

## 📋 Most Popular Tools

| No | Tool | Function | Example |
|----|------|----------|---------|
| 1 | `link-check` | Real-time HTTP link checker | `./clsdh link-check https://site.com` |
| 2 | `tcp-port` | TCP port check | `./clsdh tcp-port host.com 80` |
| 3 | `cpu-monitor` | Real-time CPU monitor | `./clsdh cpu-monitor` |
| 4 | `mem-monitor` | Real-time memory monitor | `./clsdh mem-monitor` |
| 5 | `http-headers` | View HTTP headers | `./clsdh http-headers https://site.com` |

---

## 💡 Usage Tips

1. **Use `--no-color`** for output without ANSI colors (good for logs):
   ```bash
   ./clsdh link-check https://site.com --no-color
   ```

2. **Save output to file**:
   ```bash
   ./clsdh link-check https://site.com -o result.txt
   ```

3. **Stop monitors** (CPU, Mem, Disk, Net) by pressing **Ctrl+C**.

---

## ❓ Frequently Asked Questions

**Q: Why does https:// sometimes show DOWN?**  
A: CLSDH uses raw TCP sockets without OpenSSL. For HTTPS, plain TCP connection to port 443 usually doesn't receive valid HTTP response.

**Q: How to update?**  
A: Download the latest binary from [GitHub Releases](https://github.com/iky-art/CLSDH/releases) or use `./clsdh upd` (if `UPDATE_URL` is configured).

---

## 📞 Support

Need help? Contact via **Instagram DM**: https://instagram.com/iky-art

---

> 🇬🇧 English documentation. Indonesian version available at `getting-started-id.md`.
