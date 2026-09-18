---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-09-18 11:14:00 EDT

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
| CPU Cores (start) | 35 |
| CPU Cores (end) | 25 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 103 |
| Sample Rate | 1.72/sec |
| Health Score | 108% |
| Threads | 11 |
| Allocations | 51 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 226 |
| Sample Rate | 3.77/sec |
| Health Score | 236% |
| Threads | 13 |
| Allocations | 131 |

<details>
<summary>CPU Timeline (2 unique values: 25-35 cores)</summary>

```
1789743325 35
1789743330 35
1789743335 35
1789743340 35
1789743345 35
1789743350 35
1789743355 35
1789743361 35
1789743366 35
1789743371 35
1789743376 35
1789743381 35
1789743386 35
1789743391 35
1789743396 35
1789743401 35
1789743406 35
1789743411 35
1789743416 35
1789743421 25
```
</details>

---

