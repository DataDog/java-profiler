---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-09-23 11:28:13 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 27 |
| CPU Cores (end) | 22 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 68 |
| Sample Rate | 1.13/sec |
| Health Score | 71% |
| Threads | 10 |
| Allocations | 52 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 64 |
| Sample Rate | 1.07/sec |
| Health Score | 67% |
| Threads | 13 |
| Allocations | 42 |

<details>
<summary>CPU Timeline (3 unique values: 22-27 cores)</summary>

```
1790177024 27
1790177029 24
1790177034 24
1790177039 24
1790177044 24
1790177049 24
1790177054 24
1790177059 24
1790177064 24
1790177069 24
1790177074 24
1790177079 24
1790177084 24
1790177089 24
1790177094 24
1790177099 22
1790177104 22
1790177109 22
1790177114 22
1790177119 22
```
</details>

---

