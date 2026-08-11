---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-08-11 11:57:46 EDT

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
| CPU Cores (start) | 31 |
| CPU Cores (end) | 31 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 416 |
| Sample Rate | 6.93/sec |
| Health Score | 433% |
| Threads | 8 |
| Allocations | 365 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 7 |
| Sample Rate | 0.12/sec |
| Health Score | 8% |
| Threads | 6 |
| Allocations | 5 |

<details>
<summary>CPU Timeline (2 unique values: 31-39 cores)</summary>

```
1786463530 31
1786463535 31
1786463540 31
1786463545 31
1786463550 31
1786463555 31
1786463560 31
1786463565 31
1786463570 31
1786463575 31
1786463580 31
1786463585 31
1786463590 31
1786463595 31
1786463600 39
1786463605 39
1786463610 39
1786463615 39
1786463620 39
1786463625 39
```
</details>

---

