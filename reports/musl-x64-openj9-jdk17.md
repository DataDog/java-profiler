---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-10-23 05:55:55 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 13 |
| CPU Cores (end) | 15 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 414 |
| Sample Rate | 6.90/sec |
| Health Score | 431% |
| Threads | 8 |
| Allocations | 375 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 597 |
| Sample Rate | 9.95/sec |
| Health Score | 622% |
| Threads | 8 |
| Allocations | 515 |

<details>
<summary>CPU Timeline (2 unique values: 13-15 cores)</summary>

```
1792749021 13
1792749026 13
1792749031 13
1792749036 13
1792749041 13
1792749046 13
1792749051 15
1792749056 15
1792749061 15
1792749066 15
1792749071 15
1792749076 15
1792749081 15
1792749086 15
1792749091 15
1792749096 15
1792749101 13
1792749106 13
1792749111 13
1792749116 13
```
</details>

---

