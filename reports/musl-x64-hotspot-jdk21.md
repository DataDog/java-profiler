---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-09-25 10:31:18 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 29 |
| CPU Cores (end) | 31 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 596 |
| Sample Rate | 9.93/sec |
| Health Score | 621% |
| Threads | 9 |
| Allocations | 350 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 730 |
| Sample Rate | 12.17/sec |
| Health Score | 761% |
| Threads | 10 |
| Allocations | 494 |

<details>
<summary>CPU Timeline (2 unique values: 29-31 cores)</summary>

```
1790346360 29
1790346365 29
1790346370 29
1790346375 29
1790346380 29
1790346385 29
1790346390 29
1790346395 29
1790346400 29
1790346405 31
1790346410 31
1790346415 31
1790346420 31
1790346425 31
1790346430 31
1790346435 31
1790346440 31
1790346445 29
1790346450 29
1790346455 29
```
</details>

---

