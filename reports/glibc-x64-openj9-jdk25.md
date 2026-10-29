---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-29 06:55:48 EDT

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
| CPU Cores (start) | 63 |
| CPU Cores (end) | 84 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 452 |
| Sample Rate | 7.53/sec |
| Health Score | 471% |
| Threads | 10 |
| Allocations | 412 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 598 |
| Sample Rate | 9.97/sec |
| Health Score | 623% |
| Threads | 11 |
| Allocations | 455 |

<details>
<summary>CPU Timeline (4 unique values: 63-84 cores)</summary>

```
1793271046 63
1793271051 63
1793271056 80
1793271061 80
1793271066 80
1793271071 80
1793271076 80
1793271081 80
1793271086 80
1793271091 80
1793271096 80
1793271101 80
1793271106 82
1793271111 82
1793271116 82
1793271121 82
1793271126 82
1793271131 82
1793271136 82
1793271141 82
```
</details>

---

