---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-23 11:05:02 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 88 |
| CPU Cores (end) | 85 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 662 |
| Sample Rate | 11.03/sec |
| Health Score | 689% |
| Threads | 9 |
| Allocations | 366 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 665 |
| Sample Rate | 11.08/sec |
| Health Score | 692% |
| Threads | 11 |
| Allocations | 473 |

<details>
<summary>CPU Timeline (4 unique values: 86-94 cores)</summary>

```
1795449488 88
1795449493 88
1795449498 88
1795449503 88
1795449508 90
1795449513 90
1795449518 90
1795449523 90
1795449528 90
1795449533 90
1795449538 90
1795449543 90
1795449548 90
1795449553 90
1795449558 90
1795449563 94
1795449568 94
1795449573 86
1795449578 86
1795449583 86
```
</details>

---

