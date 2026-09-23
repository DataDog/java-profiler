---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-09-23 00:59:14 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 44 |
| CPU Cores (end) | 42 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 488 |
| Sample Rate | 8.13/sec |
| Health Score | 508% |
| Threads | 9 |
| Allocations | 381 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 673 |
| Sample Rate | 11.22/sec |
| Health Score | 701% |
| Threads | 10 |
| Allocations | 478 |

<details>
<summary>CPU Timeline (5 unique values: 42-68 cores)</summary>

```
1790139273 44
1790139278 68
1790139283 68
1790139288 50
1790139293 50
1790139298 50
1790139303 50
1790139308 50
1790139313 50
1790139318 50
1790139323 51
1790139328 51
1790139333 51
1790139338 51
1790139343 42
1790139348 42
1790139353 42
1790139358 42
1790139363 42
1790139368 42
```
</details>

---

