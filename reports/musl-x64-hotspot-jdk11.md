---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-09 06:10:34 EDT

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
| CPU Cores (start) | 38 |
| CPU Cores (end) | 36 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 504 |
| Sample Rate | 8.40/sec |
| Health Score | 525% |
| Threads | 8 |
| Allocations | 331 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 993 |
| Sample Rate | 16.55/sec |
| Health Score | 1034% |
| Threads | 11 |
| Allocations | 480 |

<details>
<summary>CPU Timeline (2 unique values: 36-38 cores)</summary>

```
1791540277 38
1791540282 38
1791540287 38
1791540292 38
1791540297 38
1791540302 38
1791540307 38
1791540312 38
1791540317 38
1791540322 38
1791540327 38
1791540332 36
1791540337 36
1791540342 36
1791540347 36
1791540352 36
1791540357 36
1791540362 36
1791540367 36
1791540372 38
```
</details>

---

