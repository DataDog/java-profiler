---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-24 13:04:59 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 27 |
| CPU Cores (end) | 28 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 66 |
| Sample Rate | 1.10/sec |
| Health Score | 69% |
| Threads | 12 |
| Allocations | 52 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 219 |
| Sample Rate | 3.65/sec |
| Health Score | 228% |
| Threads | 14 |
| Allocations | 127 |

<details>
<summary>CPU Timeline (2 unique values: 27-28 cores)</summary>

```
1795543275 27
1795543280 27
1795543285 27
1795543290 27
1795543295 28
1795543300 28
1795543305 28
1795543310 28
1795543315 28
1795543320 28
1795543325 28
1795543330 28
1795543335 28
1795543340 28
1795543345 28
1795543350 28
1795543355 28
1795543360 28
1795543365 28
1795543370 28
```
</details>

---

