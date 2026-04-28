---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-04-28 12:52:03 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 22 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 674 |
| Sample Rate | 11.23/sec |
| Health Score | 702% |
| Threads | 8 |
| Allocations | 349 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 791 |
| Sample Rate | 13.18/sec |
| Health Score | 824% |
| Threads | 9 |
| Allocations | 511 |

<details>
<summary>CPU Timeline (4 unique values: 22-30 cores)</summary>

```
1777394794 22
1777394799 22
1777394804 22
1777394809 22
1777394814 22
1777394819 22
1777394824 27
1777394829 27
1777394834 27
1777394839 27
1777394844 27
1777394849 27
1777394854 25
1777394859 25
1777394864 25
1777394869 25
1777394874 25
1777394879 25
1777394884 25
1777394889 25
```
</details>

---

