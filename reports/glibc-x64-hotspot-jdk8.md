---
layout: default
title: glibc-x64-hotspot-jdk8
---

## glibc-x64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-09-20 21:20:06 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 11 |
| CPU Cores (end) | 10 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 186 |
| Sample Rate | 3.10/sec |
| Health Score | 194% |
| Threads | 6 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 286 |
| Sample Rate | 4.77/sec |
| Health Score | 298% |
| Threads | 9 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 10-11 cores)</summary>

```
1789953272 11
1789953277 11
1789953282 11
1789953287 11
1789953292 11
1789953297 11
1789953302 11
1789953307 11
1789953312 11
1789953317 11
1789953322 11
1789953327 11
1789953332 11
1789953337 11
1789953342 11
1789953347 11
1789953352 11
1789953357 10
1789953362 10
1789953367 10
```
</details>

---

