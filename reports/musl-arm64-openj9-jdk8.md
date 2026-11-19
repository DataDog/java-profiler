---
layout: default
title: musl-arm64-openj9-jdk8
---

## musl-arm64-openj9-jdk8 - ✅ PASS

**Date:** 2026-11-19 09:29:53 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 50 |
| CPU Cores (end) | 45 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 68 |
| Sample Rate | 1.13/sec |
| Health Score | 71% |
| Threads | 9 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 75 |
| Sample Rate | 1.25/sec |
| Health Score | 78% |
| Threads | 14 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (3 unique values: 45-50 cores)</summary>

```
1795098338 50
1795098343 50
1795098348 50
1795098353 50
1795098358 50
1795098363 50
1795098368 50
1795098373 50
1795098378 48
1795098383 48
1795098388 48
1795098393 48
1795098398 48
1795098403 48
1795098408 48
1795098413 48
1795098418 48
1795098423 48
1795098428 48
1795098434 48
```
</details>

---

