---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-16 07:42:01 EST

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
| CPU Cores (start) | 72 |
| CPU Cores (end) | 65 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 618 |
| Sample Rate | 10.30/sec |
| Health Score | 644% |
| Threads | 8 |
| Allocations | 393 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 802 |
| Sample Rate | 13.37/sec |
| Health Score | 836% |
| Threads | 10 |
| Allocations | 529 |

<details>
<summary>CPU Timeline (5 unique values: 65-72 cores)</summary>

```
1794832674 72
1794832679 72
1794832684 72
1794832689 72
1794832694 72
1794832699 67
1794832704 67
1794832709 67
1794832715 67
1794832720 67
1794832725 67
1794832730 67
1794832735 67
1794832740 67
1794832745 67
1794832750 69
1794832755 69
1794832760 69
1794832765 69
1794832770 71
```
</details>

---

