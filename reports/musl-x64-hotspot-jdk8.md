---
layout: default
title: musl-x64-hotspot-jdk8
---

## musl-x64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-10-13 12:35:47 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 32 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 396 |
| Sample Rate | 6.60/sec |
| Health Score | 412% |
| Threads | 9 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 531 |
| Sample Rate | 8.85/sec |
| Health Score | 553% |
| Threads | 11 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 30-32 cores)</summary>

```
1791908969 32
1791908974 32
1791908979 32
1791908984 32
1791908989 32
1791908994 30
1791908999 30
1791909004 30
1791909009 30
1791909014 30
1791909019 30
1791909024 30
1791909029 30
1791909034 30
1791909039 30
1791909044 30
1791909049 30
1791909054 30
1791909059 32
1791909064 32
```
</details>

---

