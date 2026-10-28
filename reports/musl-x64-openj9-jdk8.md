---
layout: default
title: musl-x64-openj9-jdk8
---

## musl-x64-openj9-jdk8 - ✅ PASS

**Date:** 2026-10-28 12:39:36 EDT

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
| CPU Cores (start) | 77 |
| CPU Cores (end) | 73 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 315 |
| Sample Rate | 5.25/sec |
| Health Score | 328% |
| Threads | 7 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 419 |
| Sample Rate | 6.98/sec |
| Health Score | 436% |
| Threads | 8 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (3 unique values: 73-81 cores)</summary>

```
1793205279 77
1793205284 77
1793205289 77
1793205294 77
1793205299 81
1793205304 81
1793205309 81
1793205314 73
1793205319 73
1793205324 73
1793205329 73
1793205334 73
1793205339 73
1793205344 73
1793205349 73
1793205355 73
1793205360 73
1793205365 73
1793205370 73
1793205375 73
```
</details>

---

