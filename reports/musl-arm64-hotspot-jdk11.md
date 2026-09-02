---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-02 11:43:31 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 59 |
| CPU Cores (end) | 59 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 61 |
| Sample Rate | 1.02/sec |
| Health Score | 64% |
| Threads | 8 |
| Allocations | 65 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 80 |
| Sample Rate | 1.33/sec |
| Health Score | 83% |
| Threads | 12 |
| Allocations | 52 |

<details>
<summary>CPU Timeline (2 unique values: 59-64 cores)</summary>

```
1788363454 59
1788363459 59
1788363464 59
1788363469 59
1788363474 59
1788363479 59
1788363484 59
1788363489 59
1788363494 59
1788363499 59
1788363504 59
1788363509 59
1788363514 59
1788363519 59
1788363524 59
1788363529 59
1788363534 64
1788363539 64
1788363544 59
1788363549 59
```
</details>

---

