---
layout: default
title: musl-arm64-hotspot-jdk8
---

## musl-arm64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-11-18 05:43:45 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 51 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 101 |
| Sample Rate | 1.68/sec |
| Health Score | 105% |
| Threads | 8 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 185 |
| Sample Rate | 3.08/sec |
| Health Score | 192% |
| Threads | 7 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 51-64 cores)</summary>

```
1794998196 51
1794998201 51
1794998206 51
1794998211 51
1794998216 51
1794998221 51
1794998226 51
1794998231 51
1794998236 51
1794998241 51
1794998246 51
1794998251 51
1794998256 64
1794998261 64
1794998267 64
1794998272 64
1794998277 64
1794998282 64
1794998287 64
1794998292 64
```
</details>

---

