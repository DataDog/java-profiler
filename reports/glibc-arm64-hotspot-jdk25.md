---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-16 13:03:12 EST

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
| CPU Cores (start) | 32 |
| CPU Cores (end) | 31 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 59 |
| Sample Rate | 0.98/sec |
| Health Score | 61% |
| Threads | 9 |
| Allocations | 76 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 57 |
| Sample Rate | 0.95/sec |
| Health Score | 59% |
| Threads | 13 |
| Allocations | 62 |

<details>
<summary>CPU Timeline (3 unique values: 31-34 cores)</summary>

```
1794851943 32
1794851948 32
1794851953 32
1794851958 32
1794851963 32
1794851968 32
1794851973 32
1794851978 32
1794851983 32
1794851988 32
1794851993 32
1794851998 34
1794852003 34
1794852008 34
1794852013 34
1794852018 31
1794852023 31
1794852028 31
1794852033 31
1794852038 31
```
</details>

---

