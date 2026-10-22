---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-22 17:27:07 EDT

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
| CPU Cores (start) | 53 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 287 |
| Sample Rate | 4.78/sec |
| Health Score | 299% |
| Threads | 10 |
| Allocations | 169 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 16 |
| Sample Rate | 0.27/sec |
| Health Score | 17% |
| Threads | 7 |
| Allocations | 20 |

<details>
<summary>CPU Timeline (2 unique values: 53-64 cores)</summary>

```
1792704094 53
1792704099 53
1792704104 53
1792704109 53
1792704114 53
1792704119 53
1792704124 53
1792704129 53
1792704134 53
1792704139 64
1792704144 64
1792704149 64
1792704154 64
1792704159 64
1792704164 64
1792704169 64
1792704174 64
1792704179 64
1792704184 64
1792704189 64
```
</details>

---

