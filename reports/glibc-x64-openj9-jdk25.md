---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-09-27 21:22:39 EDT

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
| CPU Cores (start) | 43 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 509 |
| Sample Rate | 8.48/sec |
| Health Score | 530% |
| Threads | 9 |
| Allocations | 378 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 566 |
| Sample Rate | 9.43/sec |
| Health Score | 589% |
| Threads | 10 |
| Allocations | 520 |

<details>
<summary>CPU Timeline (2 unique values: 43-73 cores)</summary>

```
1790558289 43
1790558294 43
1790558299 43
1790558304 43
1790558309 43
1790558314 43
1790558319 43
1790558324 43
1790558329 43
1790558334 43
1790558339 43
1790558344 43
1790558349 43
1790558354 43
1790558359 43
1790558364 73
1790558369 73
1790558374 73
1790558379 73
1790558384 73
```
</details>

---

