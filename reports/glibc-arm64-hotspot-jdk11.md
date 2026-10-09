---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-09 06:10:31 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 41 |
| CPU Cores (end) | 52 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 109 |
| Sample Rate | 1.82/sec |
| Health Score | 114% |
| Threads | 11 |
| Allocations | 62 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 338 |
| Sample Rate | 5.63/sec |
| Health Score | 352% |
| Threads | 12 |
| Allocations | 121 |

<details>
<summary>CPU Timeline (2 unique values: 41-52 cores)</summary>

```
1791540312 41
1791540317 41
1791540322 41
1791540327 41
1791540332 52
1791540337 52
1791540342 52
1791540347 52
1791540352 52
1791540357 52
1791540362 52
1791540367 52
1791540372 52
1791540377 52
1791540382 52
1791540387 52
1791540392 52
1791540397 52
1791540402 52
1791540407 52
```
</details>

---

