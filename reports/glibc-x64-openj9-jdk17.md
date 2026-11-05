---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-05 11:16:27 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 79 |
| CPU Cores (end) | 79 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 466 |
| Sample Rate | 7.77/sec |
| Health Score | 486% |
| Threads | 9 |
| Allocations | 351 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 597 |
| Sample Rate | 9.95/sec |
| Health Score | 622% |
| Threads | 10 |
| Allocations | 445 |

<details>
<summary>CPU Timeline (2 unique values: 77-79 cores)</summary>

```
1793895036 79
1793895041 79
1793895046 79
1793895051 79
1793895056 79
1793895061 79
1793895066 79
1793895071 79
1793895076 79
1793895081 79
1793895086 79
1793895091 79
1793895096 79
1793895101 79
1793895106 79
1793895111 79
1793895116 79
1793895121 79
1793895126 77
1793895131 77
```
</details>

---

