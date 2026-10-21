---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-10-21 10:48:10 EDT

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
| CPU Cores (start) | 30 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 461 |
| Sample Rate | 7.68/sec |
| Health Score | 480% |
| Threads | 8 |
| Allocations | 373 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 601 |
| Sample Rate | 10.02/sec |
| Health Score | 626% |
| Threads | 9 |
| Allocations | 458 |

<details>
<summary>CPU Timeline (2 unique values: 30-32 cores)</summary>

```
1792593847 30
1792593852 30
1792593857 30
1792593862 30
1792593867 30
1792593872 30
1792593877 30
1792593882 30
1792593887 30
1792593892 30
1792593897 30
1792593902 30
1792593907 30
1792593912 30
1792593917 30
1792593922 30
1792593927 30
1792593932 30
1792593937 32
1792593942 32
```
</details>

---

