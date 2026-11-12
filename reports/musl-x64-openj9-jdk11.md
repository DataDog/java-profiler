---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-12 10:53:47 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 80 |
| CPU Cores (end) | 80 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 609 |
| Sample Rate | 10.15/sec |
| Health Score | 634% |
| Threads | 8 |
| Allocations | 397 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1028 |
| Sample Rate | 17.13/sec |
| Health Score | 1071% |
| Threads | 10 |
| Allocations | 516 |

<details>
<summary>CPU Timeline (2 unique values: 78-80 cores)</summary>

```
1794498335 80
1794498340 80
1794498345 78
1794498350 78
1794498355 78
1794498360 78
1794498365 78
1794498370 78
1794498375 78
1794498380 80
1794498385 80
1794498390 80
1794498395 80
1794498401 80
1794498406 80
1794498411 78
1794498416 78
1794498421 78
1794498426 78
1794498431 80
```
</details>

---

