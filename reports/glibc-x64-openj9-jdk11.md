---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-28 20:47:27 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 72 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 613 |
| Sample Rate | 10.22/sec |
| Health Score | 639% |
| Threads | 8 |
| Allocations | 354 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 799 |
| Sample Rate | 13.32/sec |
| Health Score | 832% |
| Threads | 11 |
| Allocations | 527 |

<details>
<summary>CPU Timeline (6 unique values: 62-74 cores)</summary>

```
1793234640 64
1793234645 64
1793234650 64
1793234655 64
1793234660 64
1793234665 62
1793234670 62
1793234675 62
1793234680 62
1793234685 68
1793234690 68
1793234695 68
1793234700 70
1793234705 70
1793234710 72
1793234715 72
1793234720 74
1793234725 74
1793234730 72
1793234735 72
```
</details>

---

