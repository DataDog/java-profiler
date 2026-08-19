---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-08-19 06:13:36 EDT

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
| CPU Cores (start) | 76 |
| CPU Cores (end) | 60 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 420 |
| Sample Rate | 7.00/sec |
| Health Score | 438% |
| Threads | 9 |
| Allocations | 365 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 503 |
| Sample Rate | 8.38/sec |
| Health Score | 524% |
| Threads | 10 |
| Allocations | 507 |

<details>
<summary>CPU Timeline (2 unique values: 60-76 cores)</summary>

```
1787134023 76
1787134028 76
1787134033 60
1787134038 60
1787134043 60
1787134048 60
1787134053 60
1787134058 60
1787134063 60
1787134068 60
1787134073 60
1787134078 60
1787134083 60
1787134089 60
1787134094 60
1787134099 60
1787134104 60
1787134109 60
1787134114 60
1787134119 60
```
</details>

---

