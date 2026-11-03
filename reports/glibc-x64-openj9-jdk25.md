---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-03 11:25:56 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 75 |
| CPU Cores (end) | 93 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 527 |
| Sample Rate | 8.78/sec |
| Health Score | 549% |
| Threads | 9 |
| Allocations | 400 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 584 |
| Sample Rate | 9.73/sec |
| Health Score | 608% |
| Threads | 11 |
| Allocations | 438 |

<details>
<summary>CPU Timeline (5 unique values: 75-93 cores)</summary>

```
1793722833 75
1793722838 75
1793722843 75
1793722848 75
1793722853 75
1793722858 75
1793722863 75
1793722868 75
1793722873 75
1793722878 75
1793722883 75
1793722888 75
1793722893 75
1793722898 75
1793722903 75
1793722908 75
1793722913 84
1793722918 84
1793722923 84
1793722928 89
```
</details>

---

