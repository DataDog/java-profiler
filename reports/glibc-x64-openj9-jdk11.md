---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-25 16:22:54 EST

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
| CPU Cores (start) | 41 |
| CPU Cores (end) | 49 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 154 |
| Sample Rate | 2.57/sec |
| Health Score | 161% |
| Threads | 12 |
| Allocations | 57 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 29 |
| Sample Rate | 0.48/sec |
| Health Score | 30% |
| Threads | 9 |
| Allocations | 10 |

<details>
<summary>CPU Timeline (4 unique values: 41-69 cores)</summary>

```
1795641298 41
1795641303 41
1795641308 69
1795641313 69
1795641318 48
1795641323 48
1795641328 48
1795641333 48
1795641338 48
1795641343 48
1795641348 48
1795641353 48
1795641358 48
1795641364 48
1795641369 48
1795641374 48
1795641379 48
1795641384 48
1795641389 48
1795641394 48
```
</details>

---

