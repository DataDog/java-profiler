---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-05-13 07:32:03 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 62 |
| CPU Cores (end) | 60 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 547 |
| Sample Rate | 9.12/sec |
| Health Score | 570% |
| Threads | 9 |
| Allocations | 346 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 913 |
| Sample Rate | 15.22/sec |
| Health Score | 951% |
| Threads | 10 |
| Allocations | 487 |

<details>
<summary>CPU Timeline (2 unique values: 60-62 cores)</summary>

```
1778671570 62
1778671575 62
1778671580 62
1778671585 62
1778671590 62
1778671595 62
1778671600 62
1778671605 62
1778671610 60
1778671615 60
1778671620 60
1778671625 60
1778671630 60
1778671635 60
1778671640 60
1778671645 60
1778671650 60
1778671655 60
1778671660 60
1778671665 60
```
</details>

---

