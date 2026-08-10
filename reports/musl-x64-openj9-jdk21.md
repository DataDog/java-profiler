---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-08-10 11:38:33 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 7 |
| CPU Cores (end) | 9 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 420 |
| Sample Rate | 7.00/sec |
| Health Score | 438% |
| Threads | 8 |
| Allocations | 368 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 560 |
| Sample Rate | 9.33/sec |
| Health Score | 583% |
| Threads | 9 |
| Allocations | 453 |

<details>
<summary>CPU Timeline (4 unique values: 7-32 cores)</summary>

```
1786376001 7
1786376006 12
1786376011 12
1786376016 32
1786376021 32
1786376026 32
1786376031 32
1786376036 32
1786376041 32
1786376046 9
1786376051 9
1786376056 9
1786376061 9
1786376066 9
1786376071 9
1786376076 9
1786376081 9
1786376086 9
1786376091 9
1786376096 9
```
</details>

---

