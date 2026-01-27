---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-01-27 09:00:59 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 79 |
| CPU Cores (end) | 78 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 542 |
| Sample Rate | 18.07/sec |
| Health Score | 1129% |
| Threads | 11 |
| Allocations | 372 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 812 |
| Sample Rate | 27.07/sec |
| Health Score | 1692% |
| Threads | 13 |
| Allocations | 521 |

<details>
<summary>CPU Timeline (4 unique values: 78-83 cores)</summary>

```
1769514190 79
1769514195 79
1769514200 79
1769514205 81
1769514210 81
1769514215 81
1769514220 81
1769514225 83
1769514230 83
1769514235 83
1769514240 83
1769514245 83
1769514250 83
1769514255 78
1769514260 78
1769514265 78
1769514270 78
1769514275 78
1769514280 78
1769514285 78
```
</details>

---

