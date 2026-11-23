---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-23 11:06:25 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 59 |
| CPU Cores (end) | 54 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 411 |
| Sample Rate | 6.85/sec |
| Health Score | 428% |
| Threads | 9 |
| Allocations | 375 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 66 |
| Sample Rate | 1.10/sec |
| Health Score | 69% |
| Threads | 13 |
| Allocations | 36 |

<details>
<summary>CPU Timeline (4 unique values: 54-59 cores)</summary>

```
1795449562 59
1795449567 59
1795449572 59
1795449577 59
1795449582 59
1795449587 59
1795449592 59
1795449597 59
1795449602 59
1795449607 59
1795449612 57
1795449617 57
1795449622 57
1795449627 57
1795449632 57
1795449637 57
1795449642 57
1795449647 55
1795449652 55
1795449657 55
```
</details>

---

