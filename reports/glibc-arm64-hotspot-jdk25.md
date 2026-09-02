---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-09-02 11:43:29 EDT

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
| CPU Cores (start) | 24 |
| CPU Cores (end) | 29 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 81 |
| Sample Rate | 1.35/sec |
| Health Score | 84% |
| Threads | 10 |
| Allocations | 59 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 126 |
| Sample Rate | 2.10/sec |
| Health Score | 131% |
| Threads | 9 |
| Allocations | 89 |

<details>
<summary>CPU Timeline (2 unique values: 24-29 cores)</summary>

```
1788363471 24
1788363476 24
1788363481 29
1788363486 29
1788363491 24
1788363496 24
1788363501 29
1788363506 29
1788363511 29
1788363516 29
1788363521 29
1788363526 29
1788363531 29
1788363536 29
1788363541 29
1788363546 29
1788363551 29
1788363556 29
1788363561 29
1788363566 29
```
</details>

---

