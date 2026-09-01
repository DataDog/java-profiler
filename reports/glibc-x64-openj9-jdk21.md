---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-09-01 15:03:49 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 31 |
| CPU Cores (end) | 40 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 440 |
| Sample Rate | 7.33/sec |
| Health Score | 458% |
| Threads | 8 |
| Allocations | 333 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 608 |
| Sample Rate | 10.13/sec |
| Health Score | 633% |
| Threads | 10 |
| Allocations | 431 |

<details>
<summary>CPU Timeline (3 unique values: 31-48 cores)</summary>

```
1788289017 31
1788289022 48
1788289027 48
1788289032 40
1788289037 40
1788289042 40
1788289047 40
1788289052 40
1788289057 40
1788289062 40
1788289067 40
1788289072 40
1788289077 40
1788289082 40
1788289087 40
1788289092 40
1788289097 40
1788289102 40
1788289107 40
1788289112 40
```
</details>

---

