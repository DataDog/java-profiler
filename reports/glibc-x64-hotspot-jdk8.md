---
layout: default
title: glibc-x64-hotspot-jdk8
---

## glibc-x64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-10-28 01:05:54 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 58 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 180 |
| Sample Rate | 3.00/sec |
| Health Score | 188% |
| Threads | 7 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 182 |
| Sample Rate | 3.03/sec |
| Health Score | 189% |
| Threads | 7 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (3 unique values: 60-64 cores)</summary>

```
1793163638 64
1793163643 64
1793163648 64
1793163653 64
1793163658 64
1793163663 64
1793163668 64
1793163673 62
1793163678 62
1793163683 62
1793163688 62
1793163693 62
1793163698 62
1793163703 62
1793163708 62
1793163713 62
1793163718 62
1793163723 62
1793163728 62
1793163733 62
```
</details>

---

