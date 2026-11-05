---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-05 07:17:16 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 100 |
| Sample Rate | 1.67/sec |
| Health Score | 104% |
| Threads | 11 |
| Allocations | 50 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 259 |
| Sample Rate | 4.32/sec |
| Health Score | 270% |
| Threads | 13 |
| Allocations | 148 |

<details>
<summary>CPU Timeline (1 unique values: 48-48 cores)</summary>

```
1793880840 48
1793880845 48
1793880850 48
1793880855 48
1793880860 48
1793880865 48
1793880870 48
1793880875 48
1793880880 48
1793880885 48
1793880890 48
1793880895 48
1793880900 48
1793880905 48
1793880910 48
1793880915 48
1793880920 48
1793880925 48
1793880930 48
1793880935 48
```
</details>

---

