---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-23 11:05:03 EST

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
| CPU Cores (end) | 60 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 112 |
| Sample Rate | 1.87/sec |
| Health Score | 117% |
| Threads | 9 |
| Allocations | 61 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1006 |
| Sample Rate | 16.77/sec |
| Health Score | 1048% |
| Threads | 9 |
| Allocations | 499 |

<details>
<summary>CPU Timeline (3 unique values: 55-60 cores)</summary>

```
1795449478 59
1795449483 59
1795449489 59
1795449494 55
1795449499 55
1795449504 55
1795449509 55
1795449514 55
1795449519 55
1795449524 55
1795449529 55
1795449534 55
1795449539 60
1795449544 60
1795449549 60
1795449554 60
1795449559 60
1795449564 60
1795449569 60
1795449574 60
```
</details>

---

