---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-25 16:20:50 EST

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
| CPU Cores (start) | 53 |
| CPU Cores (end) | 55 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 118 |
| Sample Rate | 1.97/sec |
| Health Score | 123% |
| Threads | 8 |
| Allocations | 71 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 20 |
| Sample Rate | 0.33/sec |
| Health Score | 21% |
| Threads | 8 |
| Allocations | 9 |

<details>
<summary>CPU Timeline (2 unique values: 53-55 cores)</summary>

```
1795641345 53
1795641350 53
1795641355 53
1795641360 53
1795641365 53
1795641370 53
1795641375 53
1795641380 53
1795641385 53
1795641390 53
1795641395 53
1795641400 53
1795641405 53
1795641410 55
1795641415 55
1795641420 55
1795641425 55
1795641430 55
1795641435 55
1795641440 55
```
</details>

---

