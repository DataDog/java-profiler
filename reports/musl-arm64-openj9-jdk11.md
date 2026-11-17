---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-17 11:50:08 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 15 |
| CPU Cores (end) | 28 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 119 |
| Sample Rate | 1.98/sec |
| Health Score | 124% |
| Threads | 8 |
| Allocations | 61 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 956 |
| Sample Rate | 15.93/sec |
| Health Score | 996% |
| Threads | 9 |
| Allocations | 498 |

<details>
<summary>CPU Timeline (2 unique values: 15-28 cores)</summary>

```
1794933919 15
1794933924 28
1794933929 28
1794933934 28
1794933939 28
1794933944 28
1794933949 28
1794933954 28
1794933959 28
1794933964 28
1794933969 28
1794933974 28
1794933979 28
1794933984 28
1794933989 28
1794933994 28
1794933999 28
1794934004 28
1794934009 28
1794934014 28
```
</details>

---

