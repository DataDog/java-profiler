---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-12 07:47:06 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 36 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 94 |
| Sample Rate | 1.57/sec |
| Health Score | 98% |
| Threads | 11 |
| Allocations | 60 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 712 |
| Sample Rate | 11.87/sec |
| Health Score | 742% |
| Threads | 11 |
| Allocations | 468 |

<details>
<summary>CPU Timeline (2 unique values: 36-48 cores)</summary>

```
1794487387 36
1794487392 36
1794487397 36
1794487402 36
1794487407 36
1794487412 36
1794487417 36
1794487422 36
1794487427 36
1794487432 36
1794487438 36
1794487443 36
1794487448 36
1794487453 36
1794487458 36
1794487463 36
1794487468 36
1794487473 36
1794487478 36
1794487483 36
```
</details>

---

