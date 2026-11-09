---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-09 14:48:02 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 40 |
| CPU Cores (end) | 40 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 52 |
| Sample Rate | 0.87/sec |
| Health Score | 54% |
| Threads | 10 |
| Allocations | 61 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 471 |
| Sample Rate | 7.85/sec |
| Health Score | 491% |
| Threads | 10 |
| Allocations | 465 |

<details>
<summary>CPU Timeline (1 unique values: 40-40 cores)</summary>

```
1794253448 40
1794253453 40
1794253458 40
1794253463 40
1794253468 40
1794253473 40
1794253478 40
1794253483 40
1794253488 40
1794253493 40
1794253498 40
1794253503 40
1794253508 40
1794253513 40
1794253518 40
1794253523 40
1794253528 40
1794253533 40
1794253538 40
1794253543 40
```
</details>

---

