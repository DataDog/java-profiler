---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-08-20 13:25:46 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 96 |
| CPU Cores (end) | 88 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 499 |
| Sample Rate | 8.32/sec |
| Health Score | 520% |
| Threads | 8 |
| Allocations | 396 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 668 |
| Sample Rate | 11.13/sec |
| Health Score | 696% |
| Threads | 9 |
| Allocations | 511 |

<details>
<summary>CPU Timeline (2 unique values: 88-96 cores)</summary>

```
1787246438 96
1787246443 96
1787246448 96
1787246453 96
1787246458 96
1787246463 96
1787246468 96
1787246473 96
1787246478 88
1787246483 88
1787246488 88
1787246493 88
1787246498 88
1787246503 88
1787246508 88
1787246513 88
1787246518 88
1787246523 88
1787246528 88
1787246533 88
```
</details>

---

