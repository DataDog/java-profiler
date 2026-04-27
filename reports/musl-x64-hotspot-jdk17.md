---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-04-27 03:38:45 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 22 |
| CPU Cores (end) | 18 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 485 |
| Sample Rate | 8.08/sec |
| Health Score | 505% |
| Threads | 8 |
| Allocations | 365 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 992 |
| Sample Rate | 16.53/sec |
| Health Score | 1033% |
| Threads | 9 |
| Allocations | 471 |

<details>
<summary>CPU Timeline (3 unique values: 16-22 cores)</summary>

```
1777275239 22
1777275244 22
1777275249 22
1777275254 22
1777275259 22
1777275264 22
1777275269 18
1777275274 18
1777275279 16
1777275284 16
1777275289 16
1777275294 16
1777275299 16
1777275304 16
1777275309 18
1777275314 18
1777275319 18
1777275324 18
1777275329 18
1777275334 18
```
</details>

---

