---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-04-15 13:00:41 EDT

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
| CPU Cores (start) | 79 |
| CPU Cores (end) | 71 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 520 |
| Sample Rate | 8.67/sec |
| Health Score | 542% |
| Threads | 9 |
| Allocations | 379 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 751 |
| Sample Rate | 12.52/sec |
| Health Score | 782% |
| Threads | 10 |
| Allocations | 513 |

<details>
<summary>CPU Timeline (3 unique values: 71-79 cores)</summary>

```
1776272210 79
1776272215 79
1776272220 79
1776272225 79
1776272230 75
1776272235 75
1776272240 75
1776272245 75
1776272250 75
1776272255 75
1776272260 71
1776272265 71
1776272270 71
1776272275 71
1776272280 71
1776272285 71
1776272290 71
1776272295 71
1776272300 71
1776272305 71
```
</details>

---

