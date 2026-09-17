---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-09-17 13:55:47 EDT

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
| CPU Cores (start) | 30 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 342 |
| Sample Rate | 5.70/sec |
| Health Score | 356% |
| Threads | 8 |
| Allocations | 430 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 495 |
| Sample Rate | 8.25/sec |
| Health Score | 516% |
| Threads | 10 |
| Allocations | 483 |

<details>
<summary>CPU Timeline (2 unique values: 30-32 cores)</summary>

```
1789667391 30
1789667396 30
1789667401 30
1789667406 30
1789667411 30
1789667416 30
1789667421 30
1789667426 30
1789667431 30
1789667436 30
1789667441 30
1789667446 30
1789667451 30
1789667456 30
1789667461 32
1789667466 32
1789667471 32
1789667476 32
1789667481 32
1789667486 32
```
</details>

---

