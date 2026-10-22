---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-22 19:41:08 EDT

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 40 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 78 |
| Sample Rate | 1.30/sec |
| Health Score | 81% |
| Threads | 9 |
| Allocations | 62 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 86 |
| Sample Rate | 1.43/sec |
| Health Score | 89% |
| Threads | 13 |
| Allocations | 64 |

<details>
<summary>CPU Timeline (3 unique values: 40-48 cores)</summary>

```
1792712225 48
1792712230 48
1792712235 43
1792712240 43
1792712245 43
1792712250 43
1792712255 43
1792712260 43
1792712265 43
1792712270 43
1792712275 43
1792712280 43
1792712285 43
1792712290 43
1792712295 43
1792712300 43
1792712305 48
1792712310 48
1792712315 48
1792712320 48
```
</details>

---

