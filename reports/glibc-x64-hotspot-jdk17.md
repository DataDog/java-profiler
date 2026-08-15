---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-08-15 05:47:13 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 30 |
| CPU Cores (end) | 81 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 603 |
| Sample Rate | 10.05/sec |
| Health Score | 628% |
| Threads | 8 |
| Allocations | 333 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 661 |
| Sample Rate | 11.02/sec |
| Health Score | 689% |
| Threads | 11 |
| Allocations | 436 |

<details>
<summary>CPU Timeline (2 unique values: 30-81 cores)</summary>

```
1786786991 30
1786786996 30
1786787001 30
1786787006 30
1786787011 30
1786787016 30
1786787021 30
1786787026 30
1786787031 30
1786787036 30
1786787041 81
1786787046 81
1786787051 81
1786787056 81
1786787061 81
1786787066 81
1786787071 81
1786787076 81
1786787081 81
1786787086 81
```
</details>

---

