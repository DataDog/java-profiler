---
layout: default
title: glibc-x64-openj9-jdk8
---

## glibc-x64-openj9-jdk8 - ✅ PASS

**Date:** 2026-11-23 05:22:25 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 52 |
| CPU Cores (end) | 62 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 165 |
| Sample Rate | 2.75/sec |
| Health Score | 172% |
| Threads | 5 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 169 |
| Sample Rate | 2.82/sec |
| Health Score | 176% |
| Threads | 7 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (4 unique values: 52-62 cores)</summary>

```
1795429046 52
1795429051 52
1795429056 54
1795429061 54
1795429066 54
1795429071 54
1795429076 54
1795429081 54
1795429086 54
1795429091 54
1795429096 54
1795429101 54
1795429106 56
1795429111 56
1795429116 56
1795429121 56
1795429126 56
1795429131 56
1795429136 56
1795429141 56
```
</details>

---

