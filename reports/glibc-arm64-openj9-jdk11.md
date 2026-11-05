---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-05 00:07:54 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 26 |
| CPU Cores (end) | 14 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 62 |
| Sample Rate | 1.03/sec |
| Health Score | 64% |
| Threads | 10 |
| Allocations | 74 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 103 |
| Sample Rate | 1.72/sec |
| Health Score | 108% |
| Threads | 9 |
| Allocations | 54 |

<details>
<summary>CPU Timeline (2 unique values: 14-26 cores)</summary>

```
1793855026 26
1793855031 26
1793855036 26
1793855041 14
1793855046 14
1793855051 14
1793855056 14
1793855061 14
1793855066 14
1793855071 14
1793855076 14
1793855081 14
1793855086 14
1793855091 14
1793855096 14
1793855101 14
1793855106 14
1793855111 14
1793855116 14
1793855121 14
```
</details>

---

