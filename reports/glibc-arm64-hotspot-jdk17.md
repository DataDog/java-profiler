---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-24 12:21:54 EST

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
| CPU Cores (start) | 43 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 293 |
| Sample Rate | 4.88/sec |
| Health Score | 305% |
| Threads | 11 |
| Allocations | 174 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 243 |
| Sample Rate | 4.05/sec |
| Health Score | 253% |
| Threads | 14 |
| Allocations | 100 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1795540618 43
1795540623 43
1795540628 43
1795540633 43
1795540638 43
1795540643 43
1795540648 43
1795540653 43
1795540658 43
1795540663 48
1795540668 48
1795540673 48
1795540678 48
1795540683 48
1795540688 48
1795540693 48
1795540698 48
1795540703 43
1795540708 43
1795540713 43
```
</details>

---

