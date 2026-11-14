# 🏗️ CLSDH Architecture (English)

> In-depth explanation of internal structure, workflow, and code design of CLSDH.

---

## 🎯 Architecture Overview

CLSDH is designed as a **monolithic CLI binary** with all tools integrated into a single source file `clsdh.cpp`. No external dependencies except C++ standard library and POSIX socket.

---

## 📂 Source Directory Structure

```
clsdh.cpp
├── Global constants (PROGRAM, VERSION, ANSI colors)
├── Utilities (trim, nowTs, execCmd, sleepMs, hexColor)
├── Socket helpers (tcpConnect, udpConnect, parseHostPort)
├── Per-tool functions (toolLinkCheck, toolCpuMonitor, etc.)
├── Main dispatcher (main with tool mapping table)
└── printBanner() & printHelp()
```

---

## 🔄 Main Workflow

```
1. Argument Parsing (argc/argv)
      ↓
2. Tool Detection (list, -v, -h, or tool name)
      ↓
3. If 'upd' → Run auto-update
      ↓
4. Display ASCII Art Banner (magenta #ff00ff)
      ↓
5. Execute selected tool function
      ↓
6. Real-time output to stdout (with timestamp)
      ↓
7. Return exit code (0 = success, 1 = failure)
```

---

## 🔌 Socket Design (Network)

CLSDH uses **BSD Socket API** (POSIX):

- **TCP**: `socket()` → `connect()` with `poll()` for timeout
- **UDP**: `socket()` → `connect()` with `SO_SNDTIMEO` / `SO_RCVTIMEO`
- **Non-blocking**: All connections use non-blocking mode with `poll()` for precise timeout control

---

## ⚡ Concurrency Model

For `link-check`, CLSDH uses `std::thread` with batch processing:

```cpp
while (idx < urls.size()) {
    std::vector<std::thread> threads;
    // Create thread for each URL in batch
    for (size_t j = idx; j < end; j++) {
        threads.emplace_back(checkLink, url[j], timeout);
    }
    for (auto& t : threads) t.join(); // Wait for batch to finish
    idx = end;
}
```

- **Mutex** (`g_coutMutex`) protects output from thread conflicts
- **Atomic counters** (`g_up`, `g_down`, `g_done`) for thread-safe statistics

---

## 🎨 Colors and Display

- **ANSI Escape Code** for terminal colors
- **Truecolor (24-bit)** via `hexColor()` for `#ff00ff` (magenta)
- **Custom banner** displayed on every program run
- Output file (`-o`) stripped from ANSI color codes

---

## 🧩 Tool Mapping Table

All tools are registered in a static array in `main()`:

```cpp
static const struct { const char* name; void (*fn)(const std::vector<std::string>&); } tools[] = {
    {"link-check", toolLinkCheck},
    {"tcp-port", toolTcpPort},
    // ... 49 other tools
};
```

---

## 🔒 Code Security

- Does not use `system()` for network operations (only `popen()` for system utilities like `ping`, `whois`)
- No external networking libraries (prevents supply-chain attacks)
- All inputs validated before processing

---

> 🇬🇧 English documentation. Indonesian version available at `architecture-id.md`.
