---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-09-24 16:31:58 EDT

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
| CPU Cores (start) | 59 |
| CPU Cores (end) | 62 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 47 |
| Sample Rate | 0.78/sec |
| Health Score | 49% |
| Threads | 9 |
| Allocations | 73 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 6 |
| Sample Rate | 0.10/sec |
| Health Score | 6% |
| Threads | 6 |
| Allocations | 17 |

<details>
<summary>CPU Timeline (3 unique values: 59-64 cores)</summary>

```
1790281548 59
1790281553 59
1790281558 59
1790281563 59
1790281568 59
1790281573 59
1790281578 64
1790281583 64
1790281588 64
1790281593 64
1790281598 64
1790281603 64
1790281608 64
1790281613 64
1790281618 64
1790281623 64
1790281628 64
1790281633 64
1790281638 64
1790281643 64
```
</details>

---

