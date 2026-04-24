---
layout: default
title: musl-x64-openj9-jdk8
---

## musl-x64-openj9-jdk8 - ✅ PASS

**Date:** 2026-04-24 17:04:01 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 69 |
| CPU Cores (end) | 73 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 192 |
| Sample Rate | 3.20/sec |
| Health Score | 200% |
| Threads | 8 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 497 |
| Sample Rate | 8.28/sec |
| Health Score | 517% |
| Threads | 9 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (4 unique values: 69-75 cores)</summary>

```
1777064271 69
1777064276 69
1777064281 69
1777064286 69
1777064291 71
1777064296 71
1777064301 75
1777064306 75
1777064311 75
1777064316 73
1777064321 73
1777064326 73
1777064331 73
1777064336 73
1777064341 73
1777064346 73
1777064351 73
1777064356 73
1777064361 73
1777064366 73
```
</details>

---

