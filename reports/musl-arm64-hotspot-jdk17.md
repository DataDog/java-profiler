---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-10 18:14:39 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk17 |
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
| CPU Samples | 220 |
| Sample Rate | 3.67/sec |
| Health Score | 229% |
| Threads | 8 |
| Allocations | 148 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 251 |
| Sample Rate | 4.18/sec |
| Health Score | 261% |
| Threads | 12 |
| Allocations | 117 |

<details>
<summary>CPU Timeline (3 unique values: 32-38 cores)</summary>

```
1794352224 38
1794352229 38
1794352234 38
1794352239 38
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

