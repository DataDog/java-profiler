---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-08-26 01:04:21 EDT

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
| CPU Samples | 48 |
| Sample Rate | 0.80/sec |
| Health Score | 50% |
| Threads | 7 |
| Allocations | 79 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 174 |
| Sample Rate | 2.90/sec |
| Health Score | 181% |
| Threads | 10 |
| Allocations | 100 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1787720254 64
1787720259 64
1787720264 64
1787720269 64
1787720274 64
1787720279 64
1787720284 64
1787720289 64
1787720294 64
1787720299 64
1787720304 64
1787720309 64
1787720314 64
1787720319 64
1787720324 64
1787720329 64
1787720334 64
1787720339 64
1787720344 64
1787720349 64
```
</details>

---

