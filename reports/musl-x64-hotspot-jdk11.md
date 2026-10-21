---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-21 01:05:35 EDT

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
| CPU Cores (start) | 89 |
| CPU Cores (end) | 40 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 499 |
| Sample Rate | 8.32/sec |
| Health Score | 520% |
| Threads | 8 |
| Allocations | 359 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 698 |
| Sample Rate | 11.63/sec |
| Health Score | 727% |
| Threads | 8 |
| Allocations | 532 |

<details>
<summary>CPU Timeline (5 unique values: 40-93 cores)</summary>

```
1792558755 89
1792558760 91
1792558765 91
1792558770 91
1792558775 91
1792558780 93
1792558785 93
1792558790 93
1792558795 93
1792558801 93
1792558806 93
1792558811 93
1792558816 93
1792558821 93
1792558826 93
1792558831 93
1792558836 93
1792558841 93
1792558846 93
1792558851 60
```
</details>

---

