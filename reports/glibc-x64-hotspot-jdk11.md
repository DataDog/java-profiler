---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-08 05:09:11 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 12 |
| CPU Cores (end) | 9 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 477 |
| Sample Rate | 7.95/sec |
| Health Score | 497% |
| Threads | 8 |
| Allocations | 361 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 713 |
| Sample Rate | 11.88/sec |
| Health Score | 742% |
| Threads | 9 |
| Allocations | 440 |

<details>
<summary>CPU Timeline (2 unique values: 9-12 cores)</summary>

```
1791450264 12
1791450269 12
1791450274 12
1791450279 12
1791450284 12
1791450289 12
1791450294 12
1791450299 12
1791450304 12
1791450309 12
1791450314 12
1791450319 12
1791450324 12
1791450329 12
1791450334 9
1791450339 9
1791450344 9
1791450349 9
1791450354 9
1791450359 9
```
</details>

---

