---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-09 18:56:10 EST

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
| CPU Cores (start) | 44 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 81 |
| Sample Rate | 1.35/sec |
| Health Score | 84% |
| Threads | 10 |
| Allocations | 64 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 14 |
| Sample Rate | 0.23/sec |
| Health Score | 14% |
| Threads | 7 |
| Allocations | 16 |

<details>
<summary>CPU Timeline (3 unique values: 43-48 cores)</summary>

```
1794268301 44
1794268306 44
1794268311 44
1794268316 44
1794268321 44
1794268326 44
1794268331 44
1794268336 44
1794268341 44
1794268346 44
1794268351 48
1794268356 48
1794268361 48
1794268366 48
1794268371 48
1794268376 48
1794268381 48
1794268386 48
1794268391 43
1794268396 43
```
</details>

---

