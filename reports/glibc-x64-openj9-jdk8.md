---
layout: default
title: glibc-x64-openj9-jdk8
---

## glibc-x64-openj9-jdk8 - ✅ PASS

**Date:** 2026-11-18 03:32:29 EST

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
| CPU Cores (start) | 47 |
| CPU Cores (end) | 44 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 325 |
| Sample Rate | 5.42/sec |
| Health Score | 339% |
| Threads | 7 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 352 |
| Sample Rate | 5.87/sec |
| Health Score | 367% |
| Threads | 9 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (3 unique values: 44-64 cores)</summary>

```
1794990471 47
1794990476 47
1794990481 47
1794990486 47
1794990491 47
1794990496 47
1794990501 47
1794990506 47
1794990511 64
1794990516 64
1794990521 64
1794990526 64
1794990531 64
1794990536 64
1794990541 64
1794990546 64
1794990551 64
1794990556 64
1794990561 64
1794990566 64
```
</details>

---

