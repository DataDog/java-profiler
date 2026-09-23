---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-09-23 10:27:22 EDT

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
| CPU Cores (start) | 46 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 48 |
| Sample Rate | 0.80/sec |
| Health Score | 50% |
| Threads | 8 |
| Allocations | 39 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 7 |
| Sample Rate | 0.12/sec |
| Health Score | 8% |
| Threads | 6 |
| Allocations | 7 |

<details>
<summary>CPU Timeline (3 unique values: 44-48 cores)</summary>

```
1790173274 46
1790173279 46
1790173284 44
1790173289 44
1790173294 44
1790173299 44
1790173304 44
1790173309 44
1790173314 44
1790173319 44
1790173324 44
1790173329 44
1790173334 44
1790173339 46
1790173344 46
1790173349 46
1790173354 46
1790173359 46
1790173364 46
1790173369 48
```
</details>

---

