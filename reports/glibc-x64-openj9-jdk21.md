---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-09-24 16:31:57 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 68 |
| CPU Cores (end) | 56 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 544 |
| Sample Rate | 9.07/sec |
| Health Score | 567% |
| Threads | 9 |
| Allocations | 362 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 768 |
| Sample Rate | 12.80/sec |
| Health Score | 800% |
| Threads | 10 |
| Allocations | 441 |

<details>
<summary>CPU Timeline (4 unique values: 56-70 cores)</summary>

```
1790281553 68
1790281558 68
1790281563 68
1790281568 68
1790281573 68
1790281578 68
1790281583 70
1790281588 70
1790281593 70
1790281598 70
1790281603 58
1790281608 58
1790281613 58
1790281618 56
1790281623 56
1790281628 56
1790281633 56
1790281638 58
1790281643 58
1790281648 56
```
</details>

---

