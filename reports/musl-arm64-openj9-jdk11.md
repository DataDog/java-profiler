---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-24 16:31:57 EDT

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
| CPU Cores (start) | 50 |
| CPU Cores (end) | 45 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 103 |
| Sample Rate | 1.72/sec |
| Health Score | 108% |
| Threads | 8 |
| Allocations | 71 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 118 |
| Sample Rate | 1.97/sec |
| Health Score | 123% |
| Threads | 11 |
| Allocations | 35 |

<details>
<summary>CPU Timeline (2 unique values: 45-50 cores)</summary>

```
1790281538 50
1790281543 50
1790281548 50
1790281553 50
1790281558 50
1790281563 50
1790281568 50
1790281573 50
1790281578 50
1790281583 50
1790281588 50
1790281593 50
1790281598 50
1790281603 50
1790281608 50
1790281613 50
1790281618 50
1790281623 50
1790281628 50
1790281633 50
```
</details>

---

