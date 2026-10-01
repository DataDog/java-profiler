---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-10-01 07:20:12 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 61 |
| CPU Cores (end) | 56 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 456 |
| Sample Rate | 7.60/sec |
| Health Score | 475% |
| Threads | 9 |
| Allocations | 370 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 834 |
| Sample Rate | 13.90/sec |
| Health Score | 869% |
| Threads | 12 |
| Allocations | 429 |

<details>
<summary>CPU Timeline (2 unique values: 56-61 cores)</summary>

```
1790853320 61
1790853325 61
1790853330 61
1790853335 61
1790853340 56
1790853345 56
1790853350 56
1790853355 56
1790853360 56
1790853365 56
1790853370 56
1790853375 56
1790853380 56
1790853385 56
1790853390 56
1790853395 56
1790853400 56
1790853405 56
1790853410 56
1790853415 56
```
</details>

---

