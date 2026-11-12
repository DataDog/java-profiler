---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-12 05:01:27 EST

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
| CPU Cores (start) | 16 |
| CPU Cores (end) | 12 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 56 |
| Sample Rate | 0.93/sec |
| Health Score | 58% |
| Threads | 9 |
| Allocations | 65 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 59 |
| Sample Rate | 0.98/sec |
| Health Score | 61% |
| Threads | 13 |
| Allocations | 38 |

<details>
<summary>CPU Timeline (4 unique values: 12-16 cores)</summary>

```
1794477272 16
1794477277 13
1794477282 13
1794477287 13
1794477292 13
1794477297 13
1794477302 13
1794477307 13
1794477312 13
1794477317 13
1794477322 13
1794477327 13
1794477332 13
1794477337 15
1794477342 15
1794477347 15
1794477352 15
1794477357 15
1794477362 15
1794477367 12
```
</details>

---

