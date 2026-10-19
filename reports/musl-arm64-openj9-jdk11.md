---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-19 15:32:47 EDT

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
| CPU Cores (start) | 53 |
| CPU Cores (end) | 53 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 101 |
| Sample Rate | 1.68/sec |
| Health Score | 105% |
| Threads | 7 |
| Allocations | 62 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 92 |
| Sample Rate | 1.53/sec |
| Health Score | 96% |
| Threads | 12 |
| Allocations | 69 |

<details>
<summary>CPU Timeline (2 unique values: 48-53 cores)</summary>

```
1792438104 53
1792438109 53
1792438114 53
1792438119 53
1792438124 53
1792438129 53
1792438134 53
1792438139 53
1792438144 53
1792438149 53
1792438154 53
1792438159 53
1792438164 53
1792438169 48
1792438174 48
1792438179 48
1792438184 48
1792438189 48
1792438194 48
1792438199 48
```
</details>

---

