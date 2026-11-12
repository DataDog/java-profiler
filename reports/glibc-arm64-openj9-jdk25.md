---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-12 05:00:22 EST

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
| CPU Cores (start) | 33 |
| CPU Cores (end) | 35 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 52 |
| Sample Rate | 0.87/sec |
| Health Score | 54% |
| Threads | 9 |
| Allocations | 47 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 8 |
| Sample Rate | 0.13/sec |
| Health Score | 8% |
| Threads | 7 |
| Allocations | 7 |

<details>
<summary>CPU Timeline (2 unique values: 33-35 cores)</summary>

```
1794477257 33
1794477262 33
1794477267 33
1794477272 33
1794477277 33
1794477282 33
1794477287 33
1794477292 33
1794477297 35
1794477302 35
1794477307 35
1794477312 35
1794477317 35
1794477322 35
1794477327 35
1794477332 35
1794477337 35
1794477342 35
1794477347 35
1794477352 35
```
</details>

---

