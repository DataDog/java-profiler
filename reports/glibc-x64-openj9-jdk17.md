---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-10-08 12:05:50 EDT

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
| CPU Cores (start) | 22 |
| CPU Cores (end) | 20 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 471 |
| Sample Rate | 7.85/sec |
| Health Score | 491% |
| Threads | 8 |
| Allocations | 357 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 566 |
| Sample Rate | 9.43/sec |
| Health Score | 589% |
| Threads | 9 |
| Allocations | 438 |

<details>
<summary>CPU Timeline (2 unique values: 20-22 cores)</summary>

```
1791475195 22
1791475200 22
1791475205 22
1791475210 22
1791475215 22
1791475220 20
1791475225 20
1791475230 20
1791475235 20
1791475241 20
1791475246 20
1791475251 20
1791475256 20
1791475261 20
1791475266 20
1791475271 20
1791475276 20
1791475281 20
1791475286 20
1791475291 20
```
</details>

---

