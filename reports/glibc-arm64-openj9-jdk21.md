---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-10 18:14:37 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 46 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 534 |
| Sample Rate | 8.90/sec |
| Health Score | 556% |
| Threads | 9 |
| Allocations | 379 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 115 |
| Sample Rate | 1.92/sec |
| Health Score | 120% |
| Threads | 10 |
| Allocations | 63 |

<details>
<summary>CPU Timeline (2 unique values: 46-51 cores)</summary>

```
1794352272 46
1794352277 46
1794352282 46
1794352287 46
1794352292 46
1794352297 46
1794352302 46
1794352307 46
1794352312 46
1794352317 46
1794352322 51
1794352327 51
1794352332 51
1794352337 51
1794352342 51
1794352347 51
1794352352 51
1794352357 51
1794352362 51
1794352367 51
```
</details>

---

