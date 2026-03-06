---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-03-06 06:14:52 EST

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
| CPU Cores (start) | 24 |
| CPU Cores (end) | 24 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 95 |
| Sample Rate | 1.58/sec |
| Health Score | 99% |
| Threads | 8 |
| Allocations | 64 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 86 |
| Sample Rate | 1.43/sec |
| Health Score | 89% |
| Threads | 12 |
| Allocations | 42 |

<details>
<summary>CPU Timeline (1 unique values: 24-24 cores)</summary>

```
1772795419 24
1772795424 24
1772795429 24
1772795434 24
1772795439 24
1772795444 24
1772795449 24
1772795454 24
1772795459 24
1772795464 24
1772795469 24
1772795474 24
1772795479 24
1772795484 24
1772795489 24
1772795494 24
1772795499 24
1772795504 24
1772795509 24
1772795514 24
```
</details>

---

