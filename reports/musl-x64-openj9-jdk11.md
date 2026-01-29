---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-01-29 12:43:41 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 43 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 622 |
| Sample Rate | 20.73/sec |
| Health Score | 1296% |
| Threads | 8 |
| Allocations | 373 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 747 |
| Sample Rate | 24.90/sec |
| Health Score | 1556% |
| Threads | 10 |
| Allocations | 505 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1769708276 43
1769708281 43
1769708286 43
1769708291 43
1769708296 43
1769708301 43
1769708306 43
1769708311 43
1769708316 43
1769708321 43
1769708326 48
1769708331 48
1769708336 48
1769708341 48
1769708346 48
1769708351 48
1769708356 48
1769708361 48
1769708366 48
1769708371 48
```
</details>

---

