---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-03-11 10:47:08 EDT

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
| CPU Cores (start) | 24 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 525 |
| Sample Rate | 8.75/sec |
| Health Score | 547% |
| Threads | 9 |
| Allocations | 385 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 722 |
| Sample Rate | 12.03/sec |
| Health Score | 752% |
| Threads | 11 |
| Allocations | 518 |

<details>
<summary>CPU Timeline (4 unique values: 24-32 cores)</summary>

```
1773240046 24
1773240051 24
1773240056 24
1773240061 26
1773240066 26
1773240071 26
1773240076 26
1773240081 30
1773240086 30
1773240091 30
1773240096 30
1773240101 30
1773240106 30
1773240111 30
1773240116 30
1773240121 30
1773240126 30
1773240131 30
1773240136 30
1773240141 32
```
</details>

---

