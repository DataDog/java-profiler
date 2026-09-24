---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-09-24 05:52:00 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 31 |
| CPU Cores (end) | 40 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 56 |
| Sample Rate | 0.93/sec |
| Health Score | 58% |
| Threads | 11 |
| Allocations | 65 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 532 |
| Sample Rate | 8.87/sec |
| Health Score | 554% |
| Threads | 11 |
| Allocations | 527 |

<details>
<summary>CPU Timeline (3 unique values: 31-40 cores)</summary>

```
1790243074 31
1790243079 31
1790243084 31
1790243089 31
1790243094 31
1790243099 36
1790243104 36
1790243109 36
1790243114 36
1790243119 36
1790243124 36
1790243129 36
1790243134 36
1790243139 36
1790243144 36
1790243149 36
1790243154 36
1790243159 36
1790243164 36
1790243169 36
```
</details>

---

