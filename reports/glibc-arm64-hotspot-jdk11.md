---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-16 07:41:58 EST

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
| CPU Cores (start) | 51 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 334 |
| Sample Rate | 5.57/sec |
| Health Score | 348% |
| Threads | 11 |
| Allocations | 184 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 949 |
| Sample Rate | 15.82/sec |
| Health Score | 989% |
| Threads | 9 |
| Allocations | 474 |

<details>
<summary>CPU Timeline (2 unique values: 46-51 cores)</summary>

```
1794832695 51
1794832700 51
1794832705 51
1794832710 51
1794832715 51
1794832720 46
1794832725 46
1794832730 46
1794832735 46
1794832740 46
1794832745 46
1794832750 46
1794832755 46
1794832760 46
1794832765 46
1794832770 46
1794832775 46
1794832780 51
1794832785 51
1794832790 51
```
</details>

---

