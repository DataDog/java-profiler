---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-19 09:29:52 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk21 |
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
| CPU Samples | 241 |
| Sample Rate | 4.02/sec |
| Health Score | 251% |
| Threads | 11 |
| Allocations | 132 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 276 |
| Sample Rate | 4.60/sec |
| Health Score | 287% |
| Threads | 13 |
| Allocations | 126 |

<details>
<summary>CPU Timeline (2 unique values: 45-50 cores)</summary>

```
1795098314 50
1795098319 50
1795098324 50
1795098329 50
1795098334 45
1795098339 45
1795098344 45
1795098349 45
1795098354 45
1795098359 45
1795098364 45
1795098369 45
1795098374 45
1795098379 45
1795098384 45
1795098389 45
1795098394 45
1795098399 45
1795098404 45
1795098409 45
```
</details>

---

