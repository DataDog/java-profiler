---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-08-20 10:05:26 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk21 |
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
| CPU Samples | 93 |
| Sample Rate | 1.55/sec |
| Health Score | 97% |
| Threads | 10 |
| Allocations | 74 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 909 |
| Sample Rate | 15.15/sec |
| Health Score | 947% |
| Threads | 11 |
| Allocations | 475 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1787234412 64
1787234417 64
1787234422 64
1787234427 64
1787234432 64
1787234437 64
1787234442 64
1787234448 64
1787234453 64
1787234458 64
1787234463 64
1787234468 64
1787234473 64
1787234478 64
1787234483 64
1787234488 64
1787234493 64
1787234498 64
1787234503 64
1787234508 64
```
</details>

---

