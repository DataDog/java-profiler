---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-27 07:00:17 EDT

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
| CPU Cores (end) | 59 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 414 |
| Sample Rate | 6.90/sec |
| Health Score | 431% |
| Threads | 11 |
| Allocations | 202 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 117 |
| Sample Rate | 1.95/sec |
| Health Score | 122% |
| Threads | 11 |
| Allocations | 45 |

<details>
<summary>CPU Timeline (2 unique values: 59-64 cores)</summary>

```
1793098435 64
1793098440 64
1793098445 64
1793098450 64
1793098455 64
1793098460 64
1793098465 64
1793098470 59
1793098475 59
1793098481 59
1793098486 59
1793098491 59
1793098496 59
1793098501 59
1793098506 59
1793098511 59
1793098516 59
1793098521 59
1793098526 59
1793098531 59
```
</details>

---

