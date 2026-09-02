---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-09-02 11:44:47 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 62 |
| Sample Rate | 1.03/sec |
| Health Score | 64% |
| Threads | 7 |
| Allocations | 65 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 50 |
| Sample Rate | 0.83/sec |
| Health Score | 52% |
| Threads | 9 |
| Allocations | 40 |

<details>
<summary>CPU Timeline (2 unique values: 59-64 cores)</summary>

```
1788363459 64
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
1788363514 64
1788363519 64
1788363524 64
1788363529 64
1788363534 64
1788363539 64
1788363544 64
1788363549 64
1788363554 64
```
</details>

---

