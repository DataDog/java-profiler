---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-08-06 08:27:24 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 31 |
| CPU Cores (end) | 36 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 99 |
| Sample Rate | 1.65/sec |
| Health Score | 103% |
| Threads | 7 |
| Allocations | 79 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 240 |
| Sample Rate | 4.00/sec |
| Health Score | 250% |
| Threads | 12 |
| Allocations | 137 |

<details>
<summary>CPU Timeline (2 unique values: 31-36 cores)</summary>

```
1786018980 31
1786018985 31
1786018990 31
1786018995 31
1786019000 31
1786019005 36
1786019010 36
1786019015 31
1786019020 31
1786019025 31
1786019030 31
1786019035 31
1786019040 31
1786019045 31
1786019050 31
1786019055 31
1786019060 31
1786019065 31
1786019070 31
1786019075 36
```
</details>

---

