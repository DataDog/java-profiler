---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-10-27 07:00:13 EDT

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
| CPU Cores (start) | 14 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 108 |
| Sample Rate | 1.80/sec |
| Health Score | 112% |
| Threads | 9 |
| Allocations | 81 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 86 |
| Sample Rate | 1.43/sec |
| Health Score | 89% |
| Threads | 13 |
| Allocations | 48 |

<details>
<summary>CPU Timeline (2 unique values: 14-48 cores)</summary>

```
1793098496 14
1793098501 14
1793098506 48
1793098511 48
1793098516 48
1793098521 48
1793098526 48
1793098531 48
1793098536 48
1793098541 48
1793098546 48
1793098551 48
1793098556 48
1793098561 48
1793098566 48
1793098571 48
1793098576 48
1793098581 48
1793098586 48
1793098591 48
```
</details>

---

