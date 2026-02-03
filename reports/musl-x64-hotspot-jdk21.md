---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-02-03 10:07:27 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 32 |
| CPU Cores (end) | 58 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 499 |
| Sample Rate | 8.32/sec |
| Health Score | 520% |
| Threads | 10 |
| Allocations | 391 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 770 |
| Sample Rate | 12.83/sec |
| Health Score | 802% |
| Threads | 12 |
| Allocations | 474 |

<details>
<summary>CPU Timeline (4 unique values: 32-58 cores)</summary>

```
1770130806 32
1770130811 32
1770130816 32
1770130821 32
1770130826 35
1770130831 35
1770130836 33
1770130841 33
1770130846 33
1770130851 33
1770130856 33
1770130861 33
1770130866 33
1770130871 33
1770130876 33
1770130881 33
1770130886 33
1770130891 33
1770130896 33
1770130901 33
```
</details>

---

