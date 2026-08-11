---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-08-11 14:11:48 EDT

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
| CPU Cores (start) | 75 |
| CPU Cores (end) | 81 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 530 |
| Sample Rate | 8.83/sec |
| Health Score | 552% |
| Threads | 8 |
| Allocations | 383 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1054 |
| Sample Rate | 17.57/sec |
| Health Score | 1098% |
| Threads | 9 |
| Allocations | 502 |

<details>
<summary>CPU Timeline (4 unique values: 70-81 cores)</summary>

```
1786471690 75
1786471695 75
1786471700 75
1786471705 75
1786471710 75
1786471715 75
1786471721 75
1786471726 75
1786471731 75
1786471736 75
1786471741 75
1786471746 75
1786471751 75
1786471756 75
1786471761 75
1786471766 75
1786471771 70
1786471776 70
1786471781 70
1786471786 70
```
</details>

---

