---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-26 05:52:47 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 59 |
| CPU Cores (end) | 54 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 68 |
| Sample Rate | 1.13/sec |
| Health Score | 71% |
| Threads | 11 |
| Allocations | 60 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 10 |
| Sample Rate | 0.17/sec |
| Health Score | 11% |
| Threads | 7 |
| Allocations | 11 |

<details>
<summary>CPU Timeline (4 unique values: 53-59 cores)</summary>

```
1795690056 59
1795690061 59
1795690066 59
1795690071 59
1795690076 58
1795690081 58
1795690086 58
1795690091 53
1795690096 53
1795690101 53
1795690106 53
1795690111 53
1795690116 53
1795690121 53
1795690126 53
1795690131 53
1795690136 53
1795690141 54
1795690146 54
1795690151 54
```
</details>

---

