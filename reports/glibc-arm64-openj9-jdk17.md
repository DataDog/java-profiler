---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-12 04:59:11 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 28 |
| CPU Cores (end) | 28 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 76 |
| Sample Rate | 1.27/sec |
| Health Score | 79% |
| Threads | 8 |
| Allocations | 71 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 649 |
| Sample Rate | 10.82/sec |
| Health Score | 676% |
| Threads | 9 |
| Allocations | 470 |

<details>
<summary>CPU Timeline (2 unique values: 28-48 cores)</summary>

```
1794477236 28
1794477242 28
1794477247 28
1794477252 28
1794477257 28
1794477262 28
1794477267 28
1794477272 28
1794477277 28
1794477282 48
1794477287 48
1794477292 28
1794477297 28
1794477302 28
1794477307 28
1794477312 28
1794477317 28
1794477322 28
1794477327 28
1794477332 28
```
</details>

---

