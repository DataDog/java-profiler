---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-10 18:14:39 EST

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
| CPU Cores (start) | 38 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 61 |
| Sample Rate | 1.02/sec |
| Health Score | 64% |
| Threads | 8 |
| Allocations | 74 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 64 |
| Sample Rate | 1.07/sec |
| Health Score | 67% |
| Threads | 11 |
| Allocations | 60 |

<details>
<summary>CPU Timeline (3 unique values: 32-38 cores)</summary>

```
1794352223 38
1794352228 38
1794352233 38
1794352238 38
1794352244 38
1794352249 38
1794352254 38
1794352259 38
1794352264 33
1794352269 33
1794352274 33
1794352279 33
1794352284 33
1794352289 33
1794352294 33
1794352299 33
1794352304 33
1794352309 33
1794352314 33
1794352319 33
```
</details>

---

