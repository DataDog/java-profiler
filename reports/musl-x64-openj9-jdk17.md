---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-23 05:22:28 EST

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
| CPU Cores (start) | 30 |
| CPU Cores (end) | 63 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 569 |
| Sample Rate | 9.48/sec |
| Health Score | 592% |
| Threads | 9 |
| Allocations | 377 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 712 |
| Sample Rate | 11.87/sec |
| Health Score | 742% |
| Threads | 11 |
| Allocations | 461 |

<details>
<summary>CPU Timeline (3 unique values: 30-63 cores)</summary>

```
1795429036 30
1795429041 30
1795429046 30
1795429051 30
1795429056 30
1795429061 30
1795429066 30
1795429071 30
1795429076 30
1795429081 30
1795429086 30
1795429091 30
1795429096 30
1795429101 30
1795429106 30
1795429111 30
1795429116 30
1795429121 60
1795429126 60
1795429131 60
```
</details>

---

