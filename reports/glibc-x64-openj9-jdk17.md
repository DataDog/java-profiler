---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-25 16:22:54 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 27 |
| CPU Cores (end) | 50 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 116 |
| Sample Rate | 1.93/sec |
| Health Score | 121% |
| Threads | 11 |
| Allocations | 65 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 18 |
| Sample Rate | 0.30/sec |
| Health Score | 19% |
| Threads | 8 |
| Allocations | 14 |

<details>
<summary>CPU Timeline (4 unique values: 27-50 cores)</summary>

```
1795641294 27
1795641299 47
1795641304 47
1795641309 47
1795641314 47
1795641319 42
1795641324 42
1795641329 42
1795641334 42
1795641339 50
1795641344 50
1795641349 50
1795641354 50
1795641359 50
1795641364 50
1795641369 50
1795641374 50
1795641379 50
1795641384 50
1795641389 50
```
</details>

---

