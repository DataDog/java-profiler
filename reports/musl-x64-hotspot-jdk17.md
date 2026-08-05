---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-08-05 11:34:38 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 7 |
| CPU Cores (end) | 8 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 386 |
| Sample Rate | 6.43/sec |
| Health Score | 402% |
| Threads | 8 |
| Allocations | 389 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 590 |
| Sample Rate | 9.83/sec |
| Health Score | 614% |
| Threads | 9 |
| Allocations | 425 |

<details>
<summary>CPU Timeline (3 unique values: 7-32 cores)</summary>

```
1785943638 7
1785943643 7
1785943648 7
1785943653 7
1785943658 7
1785943663 7
1785943668 7
1785943673 7
1785943678 7
1785943683 7
1785943688 7
1785943693 7
1785943698 32
1785943703 32
1785943708 32
1785943713 32
1785943718 8
1785943723 8
1785943728 8
1785943733 8
```
</details>

---

