---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-12 07:47:09 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 83 |
| CPU Cores (end) | 80 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 605 |
| Sample Rate | 10.08/sec |
| Health Score | 630% |
| Threads | 8 |
| Allocations | 400 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 796 |
| Sample Rate | 13.27/sec |
| Health Score | 829% |
| Threads | 9 |
| Allocations | 534 |

<details>
<summary>CPU Timeline (4 unique values: 80-85 cores)</summary>

```
1794487324 83
1794487329 83
1794487334 83
1794487339 83
1794487344 83
1794487349 83
1794487354 83
1794487359 83
1794487364 83
1794487369 83
1794487374 83
1794487379 83
1794487384 83
1794487389 83
1794487394 81
1794487399 81
1794487405 83
1794487410 83
1794487415 83
1794487420 83
```
</details>

---

