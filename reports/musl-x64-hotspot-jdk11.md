---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-03 10:59:17 EST

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
| CPU Cores (start) | 45 |
| CPU Cores (end) | 47 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 537 |
| Sample Rate | 8.95/sec |
| Health Score | 559% |
| Threads | 8 |
| Allocations | 424 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 872 |
| Sample Rate | 14.53/sec |
| Health Score | 908% |
| Threads | 10 |
| Allocations | 536 |

<details>
<summary>CPU Timeline (4 unique values: 44-47 cores)</summary>

```
1793721244 45
1793721249 45
1793721254 45
1793721259 45
1793721264 45
1793721269 45
1793721274 45
1793721279 45
1793721284 45
1793721289 45
1793721294 45
1793721299 44
1793721304 44
1793721309 44
1793721314 44
1793721319 44
1793721324 46
1793721329 46
1793721334 46
1793721339 46
```
</details>

---

