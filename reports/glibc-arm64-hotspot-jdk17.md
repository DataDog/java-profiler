---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-09-23 11:28:13 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk17 |
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
| CPU Samples | 78 |
| Sample Rate | 1.30/sec |
| Health Score | 81% |
| Threads | 9 |
| Allocations | 71 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 64 |
| Sample Rate | 1.07/sec |
| Health Score | 67% |
| Threads | 11 |
| Allocations | 40 |

<details>
<summary>CPU Timeline (3 unique values: 22-27 cores)</summary>

```
1790176994 27
1790176999 27
1790177004 27
1790177009 27
1790177014 27
1790177019 27
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
```
</details>

---

