---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-05-12 04:02:14 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 63 |
| CPU Cores (end) | 63 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 599 |
| Sample Rate | 9.98/sec |
| Health Score | 624% |
| Threads | 9 |
| Allocations | 401 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 784 |
| Sample Rate | 13.07/sec |
| Health Score | 817% |
| Threads | 11 |
| Allocations | 475 |

<details>
<summary>CPU Timeline (2 unique values: 59-63 cores)</summary>

```
1778572555 63
1778572560 63
1778572565 63
1778572570 63
1778572575 63
1778572580 63
1778572585 63
1778572590 63
1778572595 63
1778572600 63
1778572605 63
1778572610 63
1778572615 63
1778572620 63
1778572625 63
1778572630 59
1778572635 59
1778572640 63
1778572645 63
1778572650 63
```
</details>

---

