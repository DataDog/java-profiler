---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-24 15:41:50 EDT

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
| CPU Cores (start) | 76 |
| CPU Cores (end) | 36 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 520 |
| Sample Rate | 8.67/sec |
| Health Score | 542% |
| Threads | 8 |
| Allocations | 355 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 796 |
| Sample Rate | 13.27/sec |
| Health Score | 829% |
| Threads | 9 |
| Allocations | 530 |

<details>
<summary>CPU Timeline (2 unique values: 36-76 cores)</summary>

```
1790278650 76
1790278655 76
1790278660 76
1790278665 76
1790278670 76
1790278675 76
1790278680 76
1790278685 76
1790278690 36
1790278695 36
1790278700 36
1790278705 36
1790278710 36
1790278715 36
1790278720 36
1790278725 36
1790278730 36
1790278735 36
1790278740 36
1790278745 36
```
</details>

---

