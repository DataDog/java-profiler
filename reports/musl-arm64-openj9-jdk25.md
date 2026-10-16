---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-16 11:26:17 EDT

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
| CPU Cores (start) | 64 |
| CPU Cores (end) | 53 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 241 |
| Sample Rate | 4.02/sec |
| Health Score | 251% |
| Threads | 10 |
| Allocations | 145 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 90 |
| Sample Rate | 1.50/sec |
| Health Score | 94% |
| Threads | 13 |
| Allocations | 47 |

<details>
<summary>CPU Timeline (2 unique values: 53-64 cores)</summary>

```
1792164006 64
1792164011 64
1792164016 64
1792164021 64
1792164026 64
1792164031 64
1792164036 64
1792164041 64
1792164046 53
1792164051 53
1792164056 53
1792164061 53
1792164066 53
1792164071 53
1792164076 53
1792164081 53
1792164086 53
1792164091 53
1792164096 53
1792164101 53
```
</details>

---

