---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-13 16:17:05 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 38 |
| CPU Cores (end) | 41 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 69 |
| Sample Rate | 1.15/sec |
| Health Score | 72% |
| Threads | 10 |
| Allocations | 40 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 60 |
| Sample Rate | 1.00/sec |
| Health Score | 62% |
| Threads | 12 |
| Allocations | 64 |

<details>
<summary>CPU Timeline (4 unique values: 38-48 cores)</summary>

```
1794604373 38
1794604378 38
1794604383 43
1794604388 43
1794604393 48
1794604398 48
1794604403 48
1794604408 48
1794604413 48
1794604418 48
1794604423 48
1794604428 43
1794604433 43
1794604438 43
1794604443 43
1794604448 43
1794604453 43
1794604458 43
1794604463 43
1794604468 41
```
</details>

---

