---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-10-23 05:57:09 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 60 |
| CPU Cores (end) | 73 |
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
| Allocations | 389 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 660 |
| Sample Rate | 11.00/sec |
| Health Score | 688% |
| Threads | 11 |
| Allocations | 428 |

<details>
<summary>CPU Timeline (4 unique values: 60-73 cores)</summary>

```
1792749075 60
1792749080 60
1792749085 60
1792749090 60
1792749095 60
1792749100 60
1792749105 60
1792749110 60
1792749115 60
1792749120 64
1792749125 64
1792749130 71
1792749135 71
1792749140 71
1792749145 71
1792749150 71
1792749155 71
1792749160 71
1792749165 73
1792749170 73
```
</details>

---

