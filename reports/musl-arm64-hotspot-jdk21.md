---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-24 13:05:01 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 43 |
| CPU Cores (end) | 47 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 95 |
| Sample Rate | 1.58/sec |
| Health Score | 99% |
| Threads | 11 |
| Allocations | 71 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 312 |
| Sample Rate | 5.20/sec |
| Health Score | 325% |
| Threads | 16 |
| Allocations | 149 |

<details>
<summary>CPU Timeline (3 unique values: 43-59 cores)</summary>

```
1795543270 43
1795543275 43
1795543280 43
1795543285 43
1795543290 43
1795543295 43
1795543300 43
1795543305 43
1795543310 43
1795543315 43
1795543320 43
1795543325 43
1795543330 43
1795543335 59
1795543340 59
1795543345 47
1795543350 47
1795543355 47
1795543360 47
1795543365 47
```
</details>

---

