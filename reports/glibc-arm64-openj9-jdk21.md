---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-24 05:55:16 EDT

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
| CPU Cores (start) | 11 |
| CPU Cores (end) | 11 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 54 |
| Sample Rate | 0.90/sec |
| Health Score | 56% |
| Threads | 10 |
| Allocations | 89 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 14 |
| Sample Rate | 0.23/sec |
| Health Score | 14% |
| Threads | 11 |
| Allocations | 6 |

<details>
<summary>CPU Timeline (3 unique values: 11-16 cores)</summary>

```
1792835513 11
1792835518 11
1792835523 11
1792835528 11
1792835533 11
1792835538 11
1792835543 11
1792835548 16
1792835553 16
1792835558 16
1792835563 16
1792835568 14
1792835573 14
1792835578 11
1792835583 11
1792835588 11
1792835593 11
1792835598 11
1792835603 11
1792835608 11
```
</details>

---

