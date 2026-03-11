---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-03-11 04:33:09 EDT

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
| CPU Cores (start) | 79 |
| CPU Cores (end) | 82 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 611 |
| Sample Rate | 10.18/sec |
| Health Score | 636% |
| Threads | 9 |
| Allocations | 360 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 755 |
| Sample Rate | 12.58/sec |
| Health Score | 786% |
| Threads | 10 |
| Allocations | 489 |

<details>
<summary>CPU Timeline (6 unique values: 67-82 cores)</summary>

```
1773217621 79
1773217626 79
1773217631 79
1773217636 79
1773217641 79
1773217646 79
1773217651 67
1773217656 67
1773217661 67
1773217666 67
1773217671 67
1773217676 70
1773217681 70
1773217686 70
1773217691 70
1773217696 70
1773217701 70
1773217706 75
1773217711 75
1773217716 75
```
</details>

---

