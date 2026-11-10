---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-10 18:15:41 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 58 |
| CPU Cores (end) | 50 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 61 |
| Sample Rate | 1.02/sec |
| Health Score | 64% |
| Threads | 10 |
| Allocations | 46 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 64 |
| Sample Rate | 1.07/sec |
| Health Score | 67% |
| Threads | 14 |
| Allocations | 50 |

<details>
<summary>CPU Timeline (3 unique values: 50-58 cores)</summary>

```
1794352284 58
1794352289 58
1794352294 58
1794352299 58
1794352304 58
1794352309 50
1794352314 50
1794352319 50
1794352324 50
1794352329 51
1794352334 51
1794352339 51
1794352344 51
1794352349 51
1794352354 51
1794352359 51
1794352364 51
1794352369 51
1794352374 51
1794352379 51
```
</details>

---

