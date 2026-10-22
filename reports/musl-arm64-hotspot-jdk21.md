---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-10-22 12:29:05 EDT

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
| CPU Cores (start) | 51 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 305 |
| Sample Rate | 5.08/sec |
| Health Score | 318% |
| Threads | 12 |
| Allocations | 153 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 97 |
| Sample Rate | 1.62/sec |
| Health Score | 101% |
| Threads | 12 |
| Allocations | 79 |

<details>
<summary>CPU Timeline (2 unique values: 46-51 cores)</summary>

```
1792686215 51
1792686220 51
1792686225 51
1792686230 51
1792686235 51
1792686240 51
1792686245 51
1792686250 51
1792686255 51
1792686260 51
1792686265 51
1792686270 51
1792686275 51
1792686280 51
1792686285 51
1792686290 51
1792686295 51
1792686300 46
1792686305 46
1792686310 46
```
</details>

---

