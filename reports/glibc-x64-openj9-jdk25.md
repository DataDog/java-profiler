---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-30 06:16:24 EDT

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
| CPU Cores (start) | 56 |
| CPU Cores (end) | 58 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 422 |
| Sample Rate | 7.03/sec |
| Health Score | 439% |
| Threads | 9 |
| Allocations | 410 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 523 |
| Sample Rate | 8.72/sec |
| Health Score | 545% |
| Threads | 10 |
| Allocations | 440 |

<details>
<summary>CPU Timeline (2 unique values: 56-58 cores)</summary>

```
1793355166 56
1793355171 56
1793355176 56
1793355181 56
1793355186 58
1793355191 58
1793355196 58
1793355201 58
1793355206 58
1793355211 58
1793355216 58
1793355221 58
1793355226 58
1793355231 58
1793355236 58
1793355241 58
1793355246 58
1793355251 58
1793355256 58
1793355261 58
```
</details>

---

