---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-09-24 05:34:55 EDT

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
| CPU Cores (start) | 64 |
| CPU Cores (end) | 24 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 310 |
| Sample Rate | 5.17/sec |
| Health Score | 323% |
| Threads | 9 |
| Allocations | 153 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 128 |
| Sample Rate | 2.13/sec |
| Health Score | 133% |
| Threads | 11 |
| Allocations | 62 |

<details>
<summary>CPU Timeline (3 unique values: 24-64 cores)</summary>

```
1790242215 64
1790242220 64
1790242225 64
1790242230 64
1790242235 64
1790242240 64
1790242245 64
1790242250 64
1790242255 64
1790242260 64
1790242265 64
1790242270 64
1790242275 64
1790242280 64
1790242285 44
1790242290 44
1790242295 44
1790242300 44
1790242305 24
1790242310 24
```
</details>

---

