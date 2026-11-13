---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-13 09:47:48 EST

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
| CPU Cores (start) | 70 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 525 |
| Sample Rate | 8.75/sec |
| Health Score | 547% |
| Threads | 8 |
| Allocations | 361 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 729 |
| Sample Rate | 12.15/sec |
| Health Score | 759% |
| Threads | 9 |
| Allocations | 549 |

<details>
<summary>CPU Timeline (2 unique values: 46-70 cores)</summary>

```
1794580925 70
1794580930 70
1794580935 70
1794580940 46
1794580945 46
1794580950 46
1794580955 46
1794580960 46
1794580965 46
1794580970 46
1794580975 46
1794580980 46
1794580985 46
1794580990 46
1794580995 46
1794581000 46
1794581005 46
1794581010 46
1794581015 46
1794581020 46
```
</details>

---

