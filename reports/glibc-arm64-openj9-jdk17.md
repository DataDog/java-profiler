---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-19 13:28:44 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 50 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 46 |
| Sample Rate | 0.77/sec |
| Health Score | 48% |
| Threads | 11 |
| Allocations | 78 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 215 |
| Sample Rate | 3.58/sec |
| Health Score | 224% |
| Threads | 10 |
| Allocations | 117 |

<details>
<summary>CPU Timeline (2 unique values: 48-50 cores)</summary>

```
1795112560 48
1795112565 48
1795112570 48
1795112575 48
1795112580 48
1795112585 48
1795112590 48
1795112595 48
1795112600 48
1795112605 48
1795112610 48
1795112615 48
1795112620 48
1795112625 48
1795112630 48
1795112635 50
1795112640 50
1795112645 50
1795112650 50
1795112655 50
```
</details>

---

