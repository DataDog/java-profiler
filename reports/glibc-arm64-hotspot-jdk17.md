---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-12 05:01:27 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk17 |
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
| CPU Samples | 259 |
| Sample Rate | 4.32/sec |
| Health Score | 270% |
| Threads | 13 |
| Allocations | 89 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 24 |
| Sample Rate | 0.40/sec |
| Health Score | 25% |
| Threads | 7 |
| Allocations | 22 |

<details>
<summary>CPU Timeline (2 unique values: 46-51 cores)</summary>

```
1794477313 46
1794477318 46
1794477323 46
1794477328 46
1794477333 46
1794477338 46
1794477343 46
1794477348 46
1794477353 46
1794477358 46
1794477363 46
1794477368 46
1794477373 46
1794477378 51
1794477383 51
1794477388 51
1794477393 51
1794477398 51
1794477403 51
1794477408 51
```
</details>

---

