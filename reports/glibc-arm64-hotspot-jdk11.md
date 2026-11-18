---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-18 05:43:43 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk11 |
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
| CPU Samples | 135 |
| Sample Rate | 2.25/sec |
| Health Score | 141% |
| Threads | 11 |
| Allocations | 63 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 899 |
| Sample Rate | 14.98/sec |
| Health Score | 936% |
| Threads | 9 |
| Allocations | 455 |

<details>
<summary>CPU Timeline (2 unique values: 51-64 cores)</summary>

```
1794998202 51
1794998207 51
1794998212 51
1794998217 51
1794998222 51
1794998227 51
1794998232 51
1794998237 51
1794998242 51
1794998247 51
1794998252 51
1794998257 64
1794998262 64
1794998267 64
1794998272 64
1794998277 64
1794998282 64
1794998287 64
1794998292 64
1794998297 64
```
</details>

---

