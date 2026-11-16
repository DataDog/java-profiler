---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-15 20:41:36 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 26 |
| CPU Cores (end) | 21 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 208 |
| Sample Rate | 3.47/sec |
| Health Score | 217% |
| Threads | 9 |
| Allocations | 145 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 10 |
| Sample Rate | 0.17/sec |
| Health Score | 11% |
| Threads | 7 |
| Allocations | 13 |

<details>
<summary>CPU Timeline (4 unique values: 19-26 cores)</summary>

```
1794793084 26
1794793089 24
1794793094 24
1794793099 24
1794793104 24
1794793109 19
1794793114 19
1794793119 19
1794793124 19
1794793129 21
1794793134 21
1794793139 21
1794793144 21
1794793149 21
1794793154 21
1794793159 21
1794793164 21
1794793169 21
1794793174 21
1794793179 21
```
</details>

---

