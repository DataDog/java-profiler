---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-09-25 10:31:16 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 43 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 327 |
| Sample Rate | 5.45/sec |
| Health Score | 341% |
| Threads | 11 |
| Allocations | 128 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 90 |
| Sample Rate | 1.50/sec |
| Health Score | 94% |
| Threads | 10 |
| Allocations | 59 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1790346407 43
1790346412 43
1790346417 43
1790346422 43
1790346427 43
1790346432 43
1790346437 43
1790346442 43
1790346447 43
1790346452 43
1790346457 48
1790346462 48
1790346467 48
1790346472 48
1790346477 48
1790346482 48
1790346487 48
1790346492 48
1790346497 48
1790346502 48
```
</details>

---

