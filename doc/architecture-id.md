# 🏗️ Arsitektur CLSDH (Bahasa Indonesia)

> Penjelasan mendalam tentang struktur internal, alur kerja, dan desain kode CLSDH.

---

## 🎯 Ringkasan Arsitektur

CLSDH dirancang sebagai **monolithic CLI binary** dengan semua tools terintegrasi dalam satu file sumber `clsdh.cpp`. Tidak ada dependensi eksternal kecuali standar library C++ dan POSIX socket.

---

## 📂 Struktur Direktori Sumber

```
clsdh.cpp
├── Konstanta global (PROGRAM, VERSION, warna ANSI)
├── Utilitas (trim, nowTs, execCmd, sleepMs, hexColor)
├── Socket helpers (tcpConnect, udpConnect, parseHostPort)
├── Fungsi tiap tool (toolLinkCheck, toolCpuMonitor, dst.)
├── Dispatcher utama (main dengan tabel pemetaan tool)
└── printBanner() & printHelp()
```

---

## 🔄 Alur Kerja Utama

```
1. Parsing Argumen (argc/argv)
      ↓
2. Deteksi Tool (list, -v, -h, atau nama tool)
      ↓
3. Jika 'upd' → Jalankan auto-update
      ↓
4. Tampilkan Banner ASCII Art (magenta #ff00ff)
      ↓
5. Eksekusi fungsi tool yang dipilih
      ↓
6. Output real-time ke stdout (dengan timestamp)
      ↓
7. Kembalikan exit code (0 = sukses, 1 = gagal)
```

---

## 🔌 Desain Socket (Jaringan)

CLSDH menggunakan **BSD Socket API** (POSIX):

- **TCP**: `socket()` → `connect()` dengan `poll()` untuk timeout
- **UDP**: `socket()` → `connect()` dengan `SO_SNDTIMEO` / `SO_RCVTIMEO`
- **Non-blocking**: Semua koneksi menggunakan mode non-blocking dengan `poll()` untuk kontrol timeout yang presisi

---

## ⚡ Model Konkuren

Untuk `link-check`, CLSDH menggunakan `std::thread` dengan batch processing:

```cpp
while (idx < urls.size()) {
    std::vector<std::thread> threads;
    // Buat thread untuk setiap URL dalam batch
    for (size_t j = idx; j < end; j++) {
        threads.emplace_back(checkLink, url[j], timeout);
    }
    for (auto& t : threads) t.join(); // Tunggu batch selesai
    idx = end;
}
```

- **Mutex** (`g_coutMutex`) melindungi output agar tidak bentrok antar thread
- **Atomic counters** (`g_up`, `g_down`, `g_done`) untuk statistik thread-safe

---

## 🎨 Warna dan Tampilan

- **ANSI Escape Code** untuk warna terminal
- **Truecolor (24-bit)** via `hexColor()` untuk `#ff00ff` (magenta)
- **Banner custom** ditampilkan pada setiap jalannya program
- Output file (`-o`) di-strip dari kode warna ANSI

---

## 🧩 Tabel Pemetaan Tool

Semua tool terdaftar dalam array statis di `main()`:

```cpp
static const struct { const char* name; void (*fn)(const std::vector<std::string>&); } tools[] = {
    {"link-check", toolLinkCheck},
    {"tcp-port", toolTcpPort},
    // ... 49 tools lainnya
};
```

---

## 🔒 Keamanan Kode

- Tidak menggunakan `system()` untuk operasi jaringan (hanya `popen()` untuk utilitas sistem seperti `ping`, `whois`)
- Tidak ada eksternal library jaringan (mencegah supply-chain attack)
- Semua input divalidasi sebelum diproses

---

> 🇮🇩 Bahasa Indonesia. Versi Inggris tersedia di `architecture-en.md`.
