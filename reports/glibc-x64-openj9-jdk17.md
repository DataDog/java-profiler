---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-10-27 07:43:58 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 59 |
| CPU Cores (end) | 70 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 432 |
| Sample Rate | 7.20/sec |
| Health Score | 450% |
| Threads | 9 |
| Allocations | 366 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 619 |
| Sample Rate | 10.32/sec |
| Health Score | 645% |
| Threads | 11 |
| Allocations | 476 |

<details>
<summary>CPU Timeline (4 unique values: 52-70 cores)</summary>

```
1793101163 59
1793101168 59
1793101173 59
1793101178 61
1793101183 61
1793101188 61
1793101193 61
1793101198 61
1793101203 61
1793101208 52
1793101213 52
1793101218 52
1793101223 52
1793101228 52
1793101233 52
1793101238 52
1793101243 52
1793101248 52
1793101253 52
1793101258 52
```
</details>

---

