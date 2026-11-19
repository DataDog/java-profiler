---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-19 09:47:44 EST

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
| CPU Cores (start) | 50 |
| CPU Cores (end) | 36 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 325 |
| Sample Rate | 5.42/sec |
| Health Score | 339% |
| Threads | 9 |
| Allocations | 149 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 98 |
| Sample Rate | 1.63/sec |
| Health Score | 102% |
| Threads | 14 |
| Allocations | 38 |

<details>
<summary>CPU Timeline (3 unique values: 31-50 cores)</summary>

```
1795099272 50
1795099277 50
1795099282 50
1795099287 50
1795099292 50
1795099297 50
1795099302 50
1795099307 50
1795099312 50
1795099317 36
1795099322 36
1795099327 36
1795099332 36
1795099337 31
1795099342 31
1795099347 31
1795099352 31
1795099357 31
1795099362 31
1795099367 31
```
</details>

---

