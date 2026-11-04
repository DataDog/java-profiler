---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-04 10:58:22 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 74 |
| CPU Cores (end) | 62 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 625 |
| Sample Rate | 10.42/sec |
| Health Score | 651% |
| Threads | 9 |
| Allocations | 364 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 641 |
| Sample Rate | 10.68/sec |
| Health Score | 668% |
| Threads | 11 |
| Allocations | 454 |

<details>
<summary>CPU Timeline (5 unique values: 60-76 cores)</summary>

```
1793807624 74
1793807629 76
1793807634 76
1793807639 76
1793807644 76
1793807649 76
1793807654 76
1793807659 76
1793807664 76
1793807669 76
1793807674 76
1793807679 76
1793807684 64
1793807689 64
1793807694 62
1793807699 62
1793807704 62
1793807709 60
1793807714 60
1793807719 60
```
</details>

---

