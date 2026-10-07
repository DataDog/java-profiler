---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-07 01:56:54 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 32 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 62 |
| Sample Rate | 1.03/sec |
| Health Score | 64% |
| Threads | 8 |
| Allocations | 64 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 99 |
| Sample Rate | 1.65/sec |
| Health Score | 103% |
| Threads | 12 |
| Allocations | 43 |

<details>
<summary>CPU Timeline (1 unique values: 32-32 cores)</summary>

```
1791352314 32
1791352319 32
1791352324 32
1791352329 32
1791352334 32
1791352339 32
1791352344 32
1791352349 32
1791352354 32
1791352359 32
1791352364 32
1791352369 32
1791352374 32
1791352379 32
1791352384 32
1791352389 32
1791352394 32
1791352399 32
1791352404 32
1791352409 32
```
</details>

---

