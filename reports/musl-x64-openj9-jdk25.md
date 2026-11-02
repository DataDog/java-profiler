---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-02 17:11:47 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 96 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 469 |
| Sample Rate | 7.82/sec |
| Health Score | 489% |
| Threads | 9 |
| Allocations | 415 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 561 |
| Sample Rate | 9.35/sec |
| Health Score | 584% |
| Threads | 11 |
| Allocations | 493 |

<details>
<summary>CPU Timeline (2 unique values: 64-96 cores)</summary>

```
1793656884 96
1793656889 96
1793656894 96
1793656899 96
1793656904 96
1793656909 96
1793656914 96
1793656919 96
1793656924 96
1793656929 96
1793656934 96
1793656939 96
1793656944 96
1793656949 96
1793656954 96
1793656959 96
1793656964 96
1793656970 96
1793656975 64
1793656980 64
```
</details>

---

