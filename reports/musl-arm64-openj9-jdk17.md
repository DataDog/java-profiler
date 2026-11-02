---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-02 17:11:46 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 43 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 72 |
| Sample Rate | 1.20/sec |
| Health Score | 75% |
| Threads | 9 |
| Allocations | 60 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 7 |
| Sample Rate | 0.12/sec |
| Health Score | 8% |
| Threads | 5 |
| Allocations | 15 |

<details>
<summary>CPU Timeline (2 unique values: 42-43 cores)</summary>

```
1793656879 43
1793656884 43
1793656889 43
1793656894 43
1793656899 43
1793656904 43
1793656909 43
1793656914 43
1793656919 43
1793656924 43
1793656929 43
1793656934 43
1793656939 43
1793656944 43
1793656949 43
1793656954 43
1793656959 42
1793656964 42
1793656969 42
1793656974 42
```
</details>

---

