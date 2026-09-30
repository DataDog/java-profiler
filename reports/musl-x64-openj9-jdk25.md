---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-09-30 10:44:07 EDT

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
| CPU Cores (start) | 50 |
| CPU Cores (end) | 70 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 450 |
| Sample Rate | 7.50/sec |
| Health Score | 469% |
| Threads | 9 |
| Allocations | 394 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 587 |
| Sample Rate | 9.78/sec |
| Health Score | 611% |
| Threads | 11 |
| Allocations | 504 |

<details>
<summary>CPU Timeline (3 unique values: 50-70 cores)</summary>

```
1790779118 50
1790779124 50
1790779129 50
1790779134 53
1790779139 53
1790779144 53
1790779149 53
1790779154 53
1790779159 53
1790779164 53
1790779169 53
1790779174 53
1790779179 53
1790779184 53
1790779189 53
1790779194 53
1790779199 53
1790779204 53
1790779209 53
1790779214 53
```
</details>

---

