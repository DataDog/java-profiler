---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-16 13:04:54 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 35 |
| CPU Cores (end) | 40 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 536 |
| Sample Rate | 8.93/sec |
| Health Score | 558% |
| Threads | 8 |
| Allocations | 403 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 627 |
| Sample Rate | 10.45/sec |
| Health Score | 653% |
| Threads | 11 |
| Allocations | 523 |

<details>
<summary>CPU Timeline (2 unique values: 35-40 cores)</summary>

```
1794851933 35
1794851938 35
1794851943 35
1794851948 35
1794851953 35
1794851958 35
1794851963 35
1794851968 35
1794851973 40
1794851978 40
1794851983 40
1794851988 40
1794851993 40
1794851998 40
1794852003 40
1794852008 40
1794852013 40
1794852018 40
1794852023 40
1794852028 40
```
</details>

---

