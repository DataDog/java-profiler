---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-09-28 10:34:18 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 32 |
| CPU Cores (end) | 21 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 548 |
| Sample Rate | 9.13/sec |
| Health Score | 571% |
| Threads | 8 |
| Allocations | 362 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 714 |
| Sample Rate | 11.90/sec |
| Health Score | 744% |
| Threads | 9 |
| Allocations | 458 |

<details>
<summary>CPU Timeline (2 unique values: 21-32 cores)</summary>

```
1790605755 32
1790605760 32
1790605765 21
1790605770 21
1790605775 21
1790605780 21
1790605785 21
1790605790 21
1790605795 21
1790605800 21
1790605805 21
1790605810 21
1790605815 21
1790605820 21
1790605825 21
1790605830 21
1790605835 21
1790605840 21
1790605845 21
1790605850 21
```
</details>

---

