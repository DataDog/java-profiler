---
layout: default
title: glibc-x64-openj9-jdk8
---

## glibc-x64-openj9-jdk8 - ✅ PASS

**Date:** 2026-11-27 08:37:40 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 90 |
| CPU Cores (end) | 92 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 31 |
| Sample Rate | 0.52/sec |
| Health Score | 32% |
| Threads | 7 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 4 |
| Sample Rate | 0.07/sec |
| Health Score | 4% |
| Threads | 4 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (3 unique values: 90-94 cores)</summary>

```
1795786347 90
1795786352 90
1795786357 90
1795786362 94
1795786367 94
1795786372 92
1795786377 92
1795786382 92
1795786387 92
1795786392 92
1795786397 92
1795786402 92
1795786407 92
1795786412 92
1795786417 92
1795786422 92
1795786427 92
1795786432 92
1795786437 92
1795786442 92
```
</details>

---

