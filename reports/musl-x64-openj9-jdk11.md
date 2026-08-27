---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-08-27 16:16:21 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 86 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 655 |
| Sample Rate | 10.92/sec |
| Health Score | 682% |
| Threads | 9 |
| Allocations | 351 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 890 |
| Sample Rate | 14.83/sec |
| Health Score | 927% |
| Threads | 9 |
| Allocations | 497 |

<details>
<summary>CPU Timeline (3 unique values: 86-96 cores)</summary>

```
1787854947 86
1787854952 86
1787854957 86
1787854962 86
1787854967 86
1787854972 86
1787854977 86
1787854982 86
1787854987 86
1787854992 86
1787854997 88
1787855002 88
1787855007 88
1787855012 88
1787855017 88
1787855022 88
1787855027 88
1787855032 88
1787855037 96
1787855042 96
```
</details>

---

