---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-03 10:59:17 EST

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
| CPU Cores (start) | 25 |
| CPU Cores (end) | 24 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 49 |
| Sample Rate | 0.82/sec |
| Health Score | 51% |
| Threads | 8 |
| Allocations | 50 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 76 |
| Sample Rate | 1.27/sec |
| Health Score | 79% |
| Threads | 13 |
| Allocations | 41 |

<details>
<summary>CPU Timeline (2 unique values: 24-25 cores)</summary>

```
1793721271 25
1793721276 25
1793721281 25
1793721286 25
1793721291 25
1793721296 25
1793721301 25
1793721306 24
1793721311 24
1793721316 24
1793721321 24
1793721326 25
1793721331 25
1793721336 25
1793721341 25
1793721346 25
1793721351 25
1793721356 24
1793721361 24
1793721366 24
```
</details>

---

