---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-09 11:10:55 EST

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
| CPU Cores (start) | 38 |
| CPU Cores (end) | 41 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 177 |
| Sample Rate | 2.95/sec |
| Health Score | 184% |
| Threads | 13 |
| Allocations | 133 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 512 |
| Sample Rate | 8.53/sec |
| Health Score | 533% |
| Threads | 10 |
| Allocations | 540 |

<details>
<summary>CPU Timeline (3 unique values: 38-43 cores)</summary>

```
1794240226 38
1794240231 38
1794240236 38
1794240241 38
1794240246 38
1794240251 38
1794240256 38
1794240261 38
1794240266 38
1794240271 43
1794240276 43
1794240281 43
1794240286 43
1794240291 43
1794240296 43
1794240301 43
1794240306 43
1794240311 43
1794240316 43
1794240321 43
```
</details>

---

