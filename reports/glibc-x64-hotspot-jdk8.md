---
layout: default
title: glibc-x64-hotspot-jdk8
---

## glibc-x64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-03-11 05:23:32 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 20 |
| CPU Cores (end) | 27 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 311 |
| Sample Rate | 5.18/sec |
| Health Score | 324% |
| Threads | 8 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 239 |
| Sample Rate | 3.98/sec |
| Health Score | 249% |
| Threads | 9 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (7 unique values: 19-29 cores)</summary>

```
1773220567 20
1773220572 20
1773220577 19
1773220582 19
1773220587 23
1773220592 23
1773220597 28
1773220602 28
1773220607 29
1773220612 29
1773220617 29
1773220622 27
1773220627 27
1773220632 27
1773220637 27
1773220642 27
1773220647 27
1773220652 27
1773220657 27
1773220662 27
```
</details>

---

