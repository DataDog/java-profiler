---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-08-07 00:56:16 EDT

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
| CPU Cores (start) | 59 |
| CPU Cores (end) | 56 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 76 |
| Sample Rate | 1.27/sec |
| Health Score | 79% |
| Threads | 10 |
| Allocations | 70 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 305 |
| Sample Rate | 5.08/sec |
| Health Score | 318% |
| Threads | 14 |
| Allocations | 147 |

<details>
<summary>CPU Timeline (3 unique values: 56-64 cores)</summary>

```
1786078346 59
1786078351 59
1786078356 64
1786078361 64
1786078366 64
1786078371 64
1786078376 64
1786078381 64
1786078386 64
1786078391 64
1786078396 64
1786078401 64
1786078406 64
1786078411 64
1786078416 64
1786078421 56
1786078426 56
1786078431 56
1786078436 56
1786078441 56
```
</details>

---

