---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-03 16:45:48 EST

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 98 |
| Sample Rate | 1.63/sec |
| Health Score | 102% |
| Threads | 12 |
| Allocations | 64 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 942 |
| Sample Rate | 15.70/sec |
| Health Score | 981% |
| Threads | 9 |
| Allocations | 490 |

<details>
<summary>CPU Timeline (1 unique values: 48-48 cores)</summary>

```
1793742034 48
1793742039 48
1793742044 48
1793742049 48
1793742054 48
1793742059 48
1793742064 48
1793742069 48
1793742074 48
1793742079 48
1793742084 48
1793742089 48
1793742094 48
1793742099 48
1793742104 48
1793742109 48
1793742114 48
1793742119 48
1793742124 48
1793742129 48
```
</details>

---

