---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-20 17:39:39 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 33 |
| CPU Cores (end) | 45 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 78 |
| Sample Rate | 1.30/sec |
| Health Score | 81% |
| Threads | 11 |
| Allocations | 73 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 12 |
| Sample Rate | 0.20/sec |
| Health Score | 12% |
| Threads | 7 |
| Allocations | 17 |

<details>
<summary>CPU Timeline (2 unique values: 33-45 cores)</summary>

```
1792532084 33
1792532089 33
1792532094 33
1792532099 33
1792532104 33
1792532109 33
1792532114 33
1792532119 33
1792532124 33
1792532129 33
1792532134 33
1792532139 33
1792532144 33
1792532149 33
1792532154 33
1792532159 33
1792532164 33
1792532169 33
1792532174 33
1792532179 45
```
</details>

---

