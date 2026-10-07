---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-10-07 17:27:42 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 70 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 504 |
| Sample Rate | 8.40/sec |
| Health Score | 525% |
| Threads | 9 |
| Allocations | 381 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 712 |
| Sample Rate | 11.87/sec |
| Health Score | 742% |
| Threads | 10 |
| Allocations | 499 |

<details>
<summary>CPU Timeline (5 unique values: 63-70 cores)</summary>

```
1791408156 64
1791408161 66
1791408166 66
1791408171 66
1791408176 66
1791408181 66
1791408186 66
1791408191 66
1791408196 66
1791408201 66
1791408206 63
1791408211 63
1791408216 65
1791408221 65
1791408226 65
1791408231 65
1791408236 65
1791408241 65
1791408246 65
1791408251 65
```
</details>

---

