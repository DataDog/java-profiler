---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-19 02:47:21 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 51 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 95 |
| Sample Rate | 1.58/sec |
| Health Score | 99% |
| Threads | 9 |
| Allocations | 64 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 103 |
| Sample Rate | 1.72/sec |
| Health Score | 108% |
| Threads | 15 |
| Allocations | 37 |

<details>
<summary>CPU Timeline (2 unique values: 46-51 cores)</summary>

```
1795074231 51
1795074236 51
1795074241 51
1795074246 51
1795074252 51
1795074257 51
1795074262 51
1795074267 51
1795074272 51
1795074277 51
1795074282 51
1795074287 51
1795074292 51
1795074297 51
1795074302 51
1795074307 51
1795074312 51
1795074317 51
1795074322 51
1795074327 51
```
</details>

---

