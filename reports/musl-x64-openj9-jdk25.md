---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-08-10 11:38:33 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 96 |
| CPU Cores (end) | 91 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 448 |
| Sample Rate | 7.47/sec |
| Health Score | 467% |
| Threads | 9 |
| Allocations | 410 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 602 |
| Sample Rate | 10.03/sec |
| Health Score | 627% |
| Threads | 10 |
| Allocations | 457 |

<details>
<summary>CPU Timeline (4 unique values: 91-96 cores)</summary>

```
1786376001 96
1786376006 96
1786376011 96
1786376016 96
1786376021 96
1786376026 96
1786376031 94
1786376036 94
1786376041 94
1786376046 94
1786376051 94
1786376056 94
1786376061 92
1786376066 92
1786376071 92
1786376076 92
1786376081 92
1786376086 92
1786376091 92
1786376096 91
```
</details>

---

