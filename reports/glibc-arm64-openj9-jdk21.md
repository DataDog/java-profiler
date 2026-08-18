---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-08-18 11:02:21 EDT

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
| CPU Cores (start) | 47 |
| CPU Cores (end) | 38 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 52 |
| Sample Rate | 0.87/sec |
| Health Score | 54% |
| Threads | 9 |
| Allocations | 80 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 52 |
| Sample Rate | 0.87/sec |
| Health Score | 54% |
| Threads | 11 |
| Allocations | 46 |

<details>
<summary>CPU Timeline (3 unique values: 38-47 cores)</summary>

```
1787065021 47
1787065026 47
1787065031 47
1787065036 47
1787065041 47
1787065046 47
1787065051 47
1787065056 47
1787065061 38
1787065066 38
1787065071 38
1787065076 38
1787065081 38
1787065086 38
1787065091 38
1787065096 38
1787065101 38
1787065106 38
1787065111 38
1787065116 38
```
</details>

---

