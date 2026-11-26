---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-26 05:52:46 EST

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
| CPU Cores (start) | 73 |
| CPU Cores (end) | 86 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 114 |
| Sample Rate | 1.90/sec |
| Health Score | 119% |
| Threads | 10 |
| Allocations | 64 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 14 |
| Sample Rate | 0.23/sec |
| Health Score | 14% |
| Threads | 7 |
| Allocations | 6 |

<details>
<summary>CPU Timeline (3 unique values: 73-86 cores)</summary>

```
1795690069 73
1795690074 73
1795690079 73
1795690084 73
1795690089 81
1795690094 81
1795690099 86
1795690104 86
1795690109 86
1795690114 86
1795690119 86
1795690124 86
1795690129 86
1795690134 86
1795690139 86
1795690144 86
1795690149 86
1795690154 86
1795690159 86
1795690164 86
```
</details>

---

