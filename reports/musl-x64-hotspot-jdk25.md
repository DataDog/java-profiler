---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-09-25 10:31:18 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 25 |
| CPU Cores (end) | 27 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 417 |
| Sample Rate | 6.95/sec |
| Health Score | 434% |
| Threads | 9 |
| Allocations | 369 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 553 |
| Sample Rate | 9.22/sec |
| Health Score | 576% |
| Threads | 11 |
| Allocations | 467 |

<details>
<summary>CPU Timeline (2 unique values: 25-27 cores)</summary>

```
1790346387 25
1790346392 25
1790346397 25
1790346402 27
1790346407 27
1790346412 27
1790346417 27
1790346422 27
1790346427 27
1790346432 27
1790346437 27
1790346442 27
1790346447 27
1790346452 27
1790346457 27
1790346462 27
1790346467 27
1790346472 27
1790346477 27
1790346482 27
```
</details>

---

