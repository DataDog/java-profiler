---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-02-10 16:50:46 EST

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
| CPU Cores (start) | 35 |
| CPU Cores (end) | 44 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 447 |
| Sample Rate | 7.45/sec |
| Health Score | 466% |
| Threads | 9 |
| Allocations | 368 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 693 |
| Sample Rate | 11.55/sec |
| Health Score | 722% |
| Threads | 9 |
| Allocations | 441 |

<details>
<summary>CPU Timeline (6 unique values: 28-44 cores)</summary>

```
1770759970 35
1770759975 35
1770759980 35
1770759985 35
1770759990 35
1770759995 35
1770760000 35
1770760005 35
1770760010 28
1770760015 28
1770760020 37
1770760025 37
1770760030 33
1770760035 33
1770760040 33
1770760045 42
1770760050 42
1770760055 42
1770760060 42
1770760065 42
```
</details>

---

