---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-11 05:29:42 EST

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
| CPU Cores (start) | 44 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 90 |
| Sample Rate | 1.50/sec |
| Health Score | 94% |
| Threads | 11 |
| Allocations | 61 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 83 |
| Sample Rate | 1.38/sec |
| Health Score | 86% |
| Threads | 10 |
| Allocations | 33 |

<details>
<summary>CPU Timeline (2 unique values: 43-44 cores)</summary>

```
1794392613 44
1794392618 44
1794392623 44
1794392628 44
1794392633 44
1794392638 44
1794392643 44
1794392648 44
1794392653 44
1794392658 44
1794392663 44
1794392668 44
1794392673 44
1794392678 44
1794392683 44
1794392688 44
1794392693 44
1794392698 44
1794392703 43
1794392708 43
```
</details>

---

