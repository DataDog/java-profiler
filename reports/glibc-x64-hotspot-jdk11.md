---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-25 10:31:17 EDT

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
| CPU Cores (start) | 96 |
| CPU Cores (end) | 66 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 493 |
| Sample Rate | 8.22/sec |
| Health Score | 514% |
| Threads | 8 |
| Allocations | 401 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 851 |
| Sample Rate | 14.18/sec |
| Health Score | 886% |
| Threads | 9 |
| Allocations | 492 |

<details>
<summary>CPU Timeline (3 unique values: 64-96 cores)</summary>

```
1790346365 96
1790346370 96
1790346375 96
1790346380 64
1790346385 64
1790346390 64
1790346395 64
1790346400 64
1790346405 64
1790346410 64
1790346415 64
1790346420 64
1790346425 66
1790346430 66
1790346435 66
1790346440 66
1790346445 66
1790346450 66
1790346455 66
1790346460 66
```
</details>

---

