---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-19 08:04:00 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 36 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 333 |
| Sample Rate | 5.55/sec |
| Health Score | 347% |
| Threads | 10 |
| Allocations | 150 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 45 |
| Sample Rate | 0.75/sec |
| Health Score | 47% |
| Threads | 11 |
| Allocations | 26 |

<details>
<summary>CPU Timeline (2 unique values: 36-48 cores)</summary>

```
1792411190 36
1792411195 36
1792411200 48
1792411205 48
1792411210 48
1792411215 48
1792411220 48
1792411225 48
1792411230 48
1792411235 48
1792411240 48
1792411245 48
1792411250 48
1792411255 48
1792411260 48
1792411265 48
1792411270 48
1792411275 48
1792411280 48
1792411285 48
```
</details>

---

