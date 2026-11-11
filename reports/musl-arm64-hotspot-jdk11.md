---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-11 05:27:40 EST

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
| CPU Cores (start) | 42 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 124 |
| Sample Rate | 2.07/sec |
| Health Score | 129% |
| Threads | 9 |
| Allocations | 53 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 422 |
| Sample Rate | 7.03/sec |
| Health Score | 439% |
| Threads | 11 |
| Allocations | 118 |

<details>
<summary>CPU Timeline (2 unique values: 42-48 cores)</summary>

```
1794392603 42
1794392608 48
1794392613 48
1794392618 48
1794392623 48
1794392628 48
1794392633 48
1794392638 48
1794392643 48
1794392648 48
1794392653 48
1794392658 48
1794392663 48
1794392668 48
1794392673 48
1794392678 48
1794392683 48
1794392688 48
1794392693 48
1794392698 48
```
</details>

---

