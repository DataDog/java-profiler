---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-08-30 21:25:13 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 80 |
| Sample Rate | 1.33/sec |
| Health Score | 83% |
| Threads | 10 |
| Allocations | 74 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 377 |
| Sample Rate | 6.28/sec |
| Health Score | 392% |
| Threads | 12 |
| Allocations | 111 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1788139265 64
1788139270 64
1788139275 64
1788139280 64
1788139285 64
1788139290 64
1788139295 64
1788139300 64
1788139305 64
1788139310 64
1788139315 64
1788139320 64
1788139325 64
1788139330 64
1788139335 64
1788139340 64
1788139345 64
1788139350 64
1788139355 64
1788139360 64
```
</details>

---

