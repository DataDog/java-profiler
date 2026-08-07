---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-08-07 12:23:58 EDT

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
| CPU Cores (start) | 64 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 461 |
| Sample Rate | 7.68/sec |
| Health Score | 480% |
| Threads | 12 |
| Allocations | 200 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 144 |
| Sample Rate | 2.40/sec |
| Health Score | 150% |
| Threads | 10 |
| Allocations | 53 |

<details>
<summary>CPU Timeline (2 unique values: 51-64 cores)</summary>

```
1786119598 64
1786119603 64
1786119608 64
1786119613 64
1786119618 64
1786119623 64
1786119628 64
1786119633 64
1786119638 64
1786119643 64
1786119648 51
1786119653 51
1786119658 51
1786119663 51
1786119668 51
1786119673 51
1786119678 51
1786119683 51
1786119688 51
1786119693 51
```
</details>

---

