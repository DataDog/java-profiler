---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-24 12:21:56 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 33 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 78 |
| Sample Rate | 1.30/sec |
| Health Score | 81% |
| Threads | 10 |
| Allocations | 75 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 324 |
| Sample Rate | 5.40/sec |
| Health Score | 338% |
| Threads | 11 |
| Allocations | 138 |

<details>
<summary>CPU Timeline (2 unique values: 33-64 cores)</summary>

```
1795540623 33
1795540628 33
1795540633 33
1795540638 33
1795540643 33
1795540648 33
1795540653 33
1795540658 33
1795540663 33
1795540668 33
1795540673 33
1795540678 33
1795540683 33
1795540688 33
1795540693 33
1795540698 33
1795540703 33
1795540708 33
1795540713 33
1795540718 64
```
</details>

---

