---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-05-12 02:56:28 EDT

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
| CPU Cores (start) | 43 |
| CPU Cores (end) | 50 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 473 |
| Sample Rate | 7.88/sec |
| Health Score | 492% |
| Threads | 9 |
| Allocations | 367 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 656 |
| Sample Rate | 10.93/sec |
| Health Score | 683% |
| Threads | 11 |
| Allocations | 516 |

<details>
<summary>CPU Timeline (4 unique values: 39-54 cores)</summary>

```
1778568637 43
1778568642 43
1778568647 43
1778568652 43
1778568657 43
1778568662 43
1778568667 43
1778568672 43
1778568677 43
1778568682 43
1778568687 43
1778568692 43
1778568697 39
1778568702 39
1778568707 39
1778568712 39
1778568717 54
1778568722 54
1778568727 54
1778568732 54
```
</details>

---

