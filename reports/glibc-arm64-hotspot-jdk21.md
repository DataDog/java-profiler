---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-12 06:55:44 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 33 |
| CPU Cores (end) | 34 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 303 |
| Sample Rate | 5.05/sec |
| Health Score | 316% |
| Threads | 11 |
| Allocations | 140 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 256 |
| Sample Rate | 4.27/sec |
| Health Score | 267% |
| Threads | 11 |
| Allocations | 105 |

<details>
<summary>CPU Timeline (3 unique values: 33-39 cores)</summary>

```
1794484201 33
1794484206 33
1794484211 33
1794484216 33
1794484221 33
1794484226 33
1794484231 33
1794484236 33
1794484241 33
1794484246 33
1794484251 33
1794484256 33
1794484261 39
1794484266 39
1794484271 34
1794484276 34
1794484281 34
1794484286 34
1794484291 34
1794484296 34
```
</details>

---

