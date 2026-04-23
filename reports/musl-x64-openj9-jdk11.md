---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-04-23 15:03:18 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 62 |
| CPU Cores (end) | 56 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 530 |
| Sample Rate | 8.83/sec |
| Health Score | 552% |
| Threads | 9 |
| Allocations | 385 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 686 |
| Sample Rate | 11.43/sec |
| Health Score | 714% |
| Threads | 9 |
| Allocations | 529 |

<details>
<summary>CPU Timeline (5 unique values: 56-62 cores)</summary>

```
1776970685 62
1776970690 62
1776970695 62
1776970700 57
1776970705 57
1776970710 61
1776970715 61
1776970720 61
1776970725 61
1776970730 61
1776970735 61
1776970740 61
1776970745 61
1776970750 61
1776970755 58
1776970760 58
1776970765 58
1776970771 58
1776970776 58
1776970781 58
```
</details>

---

