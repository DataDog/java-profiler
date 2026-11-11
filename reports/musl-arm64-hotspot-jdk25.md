---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-11 05:05:55 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 51 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 56 |
| Sample Rate | 0.93/sec |
| Health Score | 58% |
| Threads | 10 |
| Allocations | 68 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 52 |
| Sample Rate | 0.87/sec |
| Health Score | 54% |
| Threads | 10 |
| Allocations | 33 |

<details>
<summary>CPU Timeline (3 unique values: 49-51 cores)</summary>

```
1794391226 51
1794391231 51
1794391236 51
1794391241 49
1794391246 49
1794391251 49
1794391256 49
1794391261 49
1794391266 49
1794391271 49
1794391276 49
1794391281 49
1794391286 49
1794391291 50
1794391296 50
1794391301 50
1794391306 50
1794391311 50
1794391316 50
1794391321 50
```
</details>

---

