---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-20 05:01:33 EST

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
| CPU Cores (start) | 50 |
| CPU Cores (end) | 50 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 88 |
| Sample Rate | 1.47/sec |
| Health Score | 92% |
| Threads | 8 |
| Allocations | 66 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 359 |
| Sample Rate | 5.98/sec |
| Health Score | 374% |
| Threads | 11 |
| Allocations | 119 |

<details>
<summary>CPU Timeline (2 unique values: 50-64 cores)</summary>

```
1795168601 50
1795168606 50
1795168611 50
1795168616 50
1795168621 50
1795168626 50
1795168631 50
1795168636 50
1795168641 50
1795168646 50
1795168651 50
1795168656 50
1795168661 50
1795168666 50
1795168671 50
1795168676 50
1795168681 50
1795168686 50
1795168691 50
1795168696 64
```
</details>

---

