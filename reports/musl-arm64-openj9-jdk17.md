---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-04-27 16:29:17 EDT

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
| CPU Cores (start) | 60 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 480 |
| Sample Rate | 8.00/sec |
| Health Score | 500% |
| Threads | 9 |
| Allocations | 380 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 20 |
| Sample Rate | 0.33/sec |
| Health Score | 21% |
| Threads | 10 |
| Allocations | 18 |

<details>
<summary>CPU Timeline (2 unique values: 60-64 cores)</summary>

```
1777321174 60
1777321179 60
1777321184 60
1777321189 60
1777321194 60
1777321199 60
1777321204 60
1777321209 60
1777321214 60
1777321220 64
1777321225 64
1777321230 64
1777321235 64
1777321240 64
1777321245 64
1777321250 64
1777321255 64
1777321260 64
1777321265 64
1777321270 64
```
</details>

---

