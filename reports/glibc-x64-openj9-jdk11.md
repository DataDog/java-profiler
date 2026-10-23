---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-23 19:01:52 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 67 |
| CPU Cores (end) | 73 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 520 |
| Sample Rate | 8.67/sec |
| Health Score | 542% |
| Threads | 8 |
| Allocations | 348 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 968 |
| Sample Rate | 16.13/sec |
| Health Score | 1008% |
| Threads | 9 |
| Allocations | 532 |

<details>
<summary>CPU Timeline (5 unique values: 65-75 cores)</summary>

```
1792796149 67
1792796154 65
1792796159 65
1792796164 65
1792796169 65
1792796174 65
1792796179 65
1792796184 69
1792796189 69
1792796194 73
1792796199 73
1792796204 73
1792796209 73
1792796214 73
1792796219 73
1792796224 73
1792796229 73
1792796234 73
1792796239 75
1792796244 75
```
</details>

---

