---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-12 18:03:50 EST

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
| CPU Cores (start) | 44 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 241 |
| Sample Rate | 4.02/sec |
| Health Score | 251% |
| Threads | 12 |
| Allocations | 143 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 233 |
| Sample Rate | 3.88/sec |
| Health Score | 242% |
| Threads | 14 |
| Allocations | 93 |

<details>
<summary>CPU Timeline (2 unique values: 44-48 cores)</summary>

```
1794524391 44
1794524396 44
1794524401 44
1794524406 44
1794524411 48
1794524416 48
1794524421 48
1794524426 48
1794524431 48
1794524436 48
1794524441 48
1794524446 48
1794524451 48
1794524456 48
1794524461 48
1794524466 48
1794524471 48
1794524476 48
1794524481 48
1794524486 48
```
</details>

---

