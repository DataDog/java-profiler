---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-09-27 21:22:39 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 19 |
| CPU Cores (end) | 49 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 519 |
| Sample Rate | 8.65/sec |
| Health Score | 541% |
| Threads | 8 |
| Allocations | 359 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 585 |
| Sample Rate | 9.75/sec |
| Health Score | 609% |
| Threads | 10 |
| Allocations | 461 |

<details>
<summary>CPU Timeline (2 unique values: 19-49 cores)</summary>

```
1790558304 19
1790558309 19
1790558314 19
1790558319 19
1790558324 19
1790558329 19
1790558334 19
1790558339 19
1790558344 49
1790558349 49
1790558354 49
1790558359 49
1790558364 49
1790558369 49
1790558374 49
1790558379 49
1790558384 49
1790558389 49
1790558394 49
1790558399 49
```
</details>

---

