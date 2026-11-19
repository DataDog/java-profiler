---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-19 05:18:02 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 40 |
| CPU Cores (end) | 79 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 747 |
| Sample Rate | 12.45/sec |
| Health Score | 778% |
| Threads | 9 |
| Allocations | 354 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 754 |
| Sample Rate | 12.57/sec |
| Health Score | 786% |
| Threads | 10 |
| Allocations | 477 |

<details>
<summary>CPU Timeline (7 unique values: 40-87 cores)</summary>

```
1795083218 40
1795083223 51
1795083228 51
1795083233 51
1795083238 51
1795083243 51
1795083248 51
1795083253 51
1795083258 51
1795083263 53
1795083269 53
1795083274 62
1795083279 62
1795083284 62
1795083289 67
1795083294 67
1795083299 87
1795083304 87
1795083309 87
1795083314 79
```
</details>

---

