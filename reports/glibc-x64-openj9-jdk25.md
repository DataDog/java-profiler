---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ❌ FAIL

**Date:** 2026-09-01 15:03:50 EDT

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
| CPU Cores (start) | 94 |
| CPU Cores (end) | 94 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 514 |
| Sample Rate | 8.57/sec |
| Health Score | 536% |
| Threads | 10 |
| Allocations | 397 |

#### Scenario 2: Tracer+Profiler ❌
| Metric | Value |
|--------|-------|
| Status | FAIL |
| CPU Samples | 0 |
| Sample Rate | 0.00/sec |
| Health Score | 0% |
| Threads | 0 |
| Allocations | 485 |

<details>
<summary>CPU Timeline (2 unique values: 92-94 cores)</summary>

```
1788289018 94
1788289024 94
1788289029 94
1788289034 94
1788289039 94
1788289044 94
1788289049 94
1788289054 94
1788289059 94
1788289064 94
1788289069 94
1788289074 94
1788289079 94
1788289084 94
1788289089 94
1788289094 94
1788289099 94
1788289104 94
1788289109 94
1788289114 94
```
</details>

---

