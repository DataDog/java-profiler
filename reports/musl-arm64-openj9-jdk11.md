---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-17 10:02:50 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 103 |
| Sample Rate | 1.72/sec |
| Health Score | 108% |
| Threads | 9 |
| Allocations | 51 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 982 |
| Sample Rate | 16.37/sec |
| Health Score | 1023% |
| Threads | 9 |
| Allocations | 522 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1794927343 64
1794927348 64
1794927353 64
1794927358 64
1794927363 64
1794927368 64
1794927373 64
1794927378 64
1794927383 64
1794927388 64
1794927393 64
1794927398 64
1794927403 64
1794927408 64
1794927413 64
1794927418 64
1794927423 64
1794927428 64
1794927433 64
1794927438 64
```
</details>

---

