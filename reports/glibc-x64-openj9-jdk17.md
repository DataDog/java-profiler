---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-10-14 12:30:11 EDT

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
| CPU Cores (start) | 29 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 399 |
| Sample Rate | 6.65/sec |
| Health Score | 416% |
| Threads | 8 |
| Allocations | 367 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 481 |
| Sample Rate | 8.02/sec |
| Health Score | 501% |
| Threads | 8 |
| Allocations | 478 |

<details>
<summary>CPU Timeline (2 unique values: 29-32 cores)</summary>

```
1791995077 29
1791995082 29
1791995088 29
1791995093 29
1791995098 29
1791995103 29
1791995108 29
1791995113 29
1791995118 29
1791995123 29
1791995128 29
1791995133 29
1791995138 29
1791995143 29
1791995148 32
1791995153 32
1791995158 32
1791995163 32
1791995168 32
1791995173 32
```
</details>

---

