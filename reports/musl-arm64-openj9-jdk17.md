---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-16 11:32:06 EST

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 65 |
| Sample Rate | 1.08/sec |
| Health Score | 68% |
| Threads | 10 |
| Allocations | 74 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 64 |
| Sample Rate | 1.07/sec |
| Health Score | 67% |
| Threads | 12 |
| Allocations | 44 |

<details>
<summary>CPU Timeline (2 unique values: 47-48 cores)</summary>

```
1794846377 48
1794846382 47
1794846387 47
1794846392 47
1794846397 47
1794846402 47
1794846407 47
1794846412 47
1794846417 48
1794846422 48
1794846427 48
1794846432 48
1794846437 48
1794846442 48
1794846447 48
1794846452 48
1794846457 48
1794846462 48
1794846467 48
1794846472 48
```
</details>

---

