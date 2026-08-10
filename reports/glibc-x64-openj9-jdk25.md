---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-08-10 11:38:32 EDT

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
| CPU Cores (start) | 59 |
| CPU Cores (end) | 61 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 423 |
| Sample Rate | 7.05/sec |
| Health Score | 441% |
| Threads | 10 |
| Allocations | 401 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 508 |
| Sample Rate | 8.47/sec |
| Health Score | 529% |
| Threads | 10 |
| Allocations | 494 |

<details>
<summary>CPU Timeline (2 unique values: 59-61 cores)</summary>

```
1786376016 59
1786376021 59
1786376026 59
1786376031 59
1786376036 59
1786376041 59
1786376046 59
1786376051 59
1786376056 59
1786376061 59
1786376066 59
1786376071 61
1786376076 61
1786376081 61
1786376086 61
1786376091 61
1786376096 61
1786376101 61
1786376106 61
1786376111 61
```
</details>

---

