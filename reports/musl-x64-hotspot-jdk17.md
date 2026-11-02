---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-02 17:11:46 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 60 |
| CPU Cores (end) | 58 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 495 |
| Sample Rate | 8.25/sec |
| Health Score | 516% |
| Threads | 8 |
| Allocations | 404 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 894 |
| Sample Rate | 14.90/sec |
| Health Score | 931% |
| Threads | 11 |
| Allocations | 505 |

<details>
<summary>CPU Timeline (2 unique values: 58-60 cores)</summary>

```
1793656884 60
1793656889 60
1793656894 60
1793656899 60
1793656904 60
1793656909 60
1793656914 60
1793656919 60
1793656924 60
1793656929 60
1793656934 60
1793656939 60
1793656944 60
1793656949 60
1793656954 60
1793656959 60
1793656964 60
1793656969 60
1793656974 58
1793656979 58
```
</details>

---

