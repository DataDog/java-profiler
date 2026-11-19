---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-19 05:18:00 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 39 |
| CPU Cores (end) | 49 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 61 |
| Sample Rate | 1.02/sec |
| Health Score | 64% |
| Threads | 10 |
| Allocations | 62 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 650 |
| Sample Rate | 10.83/sec |
| Health Score | 677% |
| Threads | 9 |
| Allocations | 506 |

<details>
<summary>CPU Timeline (3 unique values: 39-51 cores)</summary>

```
1795083204 39
1795083209 51
1795083214 51
1795083219 51
1795083224 51
1795083229 51
1795083234 51
1795083239 49
1795083244 49
1795083249 49
1795083254 49
1795083259 49
1795083264 49
1795083269 49
1795083274 49
1795083279 49
1795083284 49
1795083289 49
1795083294 49
1795083299 49
```
</details>

---

