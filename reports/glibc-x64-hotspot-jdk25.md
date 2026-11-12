---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-12 07:47:07 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 96 |
| CPU Cores (end) | 63 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 421 |
| Sample Rate | 7.02/sec |
| Health Score | 439% |
| Threads | 9 |
| Allocations | 390 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 503 |
| Sample Rate | 8.38/sec |
| Health Score | 524% |
| Threads | 11 |
| Allocations | 504 |

<details>
<summary>CPU Timeline (2 unique values: 63-96 cores)</summary>

```
1794487374 96
1794487379 96
1794487384 96
1794487389 96
1794487395 96
1794487400 96
1794487405 96
1794487410 96
1794487415 96
1794487420 96
1794487425 96
1794487430 96
1794487435 96
1794487440 96
1794487445 96
1794487450 96
1794487455 96
1794487460 96
1794487465 96
1794487470 96
```
</details>

---

