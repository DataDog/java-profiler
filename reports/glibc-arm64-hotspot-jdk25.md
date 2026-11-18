---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-18 09:06:19 EST

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
| CPU Cores (start) | 33 |
| CPU Cores (end) | 38 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 146 |
| Sample Rate | 2.43/sec |
| Health Score | 152% |
| Threads | 7 |
| Allocations | 70 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 123 |
| Sample Rate | 2.05/sec |
| Health Score | 128% |
| Threads | 10 |
| Allocations | 71 |

<details>
<summary>CPU Timeline (2 unique values: 33-38 cores)</summary>

```
1795010560 33
1795010565 33
1795010570 33
1795010575 33
1795010580 33
1795010585 33
1795010590 33
1795010595 33
1795010600 33
1795010605 33
1795010610 33
1795010615 33
1795010620 33
1795010625 33
1795010630 38
1795010635 38
1795010640 38
1795010645 38
1795010650 38
1795010655 38
```
</details>

---

