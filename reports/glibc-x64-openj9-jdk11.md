---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-12 07:47:07 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 93 |
| CPU Cores (end) | 67 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 515 |
| Sample Rate | 8.58/sec |
| Health Score | 536% |
| Threads | 8 |
| Allocations | 388 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 695 |
| Sample Rate | 11.58/sec |
| Health Score | 724% |
| Threads | 10 |
| Allocations | 539 |

<details>
<summary>CPU Timeline (2 unique values: 67-93 cores)</summary>

```
1794487339 93
1794487344 93
1794487349 67
1794487354 67
1794487359 67
1794487364 67
1794487369 67
1794487374 67
1794487379 67
1794487384 67
1794487389 67
1794487394 67
1794487399 67
1794487404 67
1794487409 67
1794487414 67
1794487419 67
1794487424 67
1794487429 67
1794487434 67
```
</details>

---

