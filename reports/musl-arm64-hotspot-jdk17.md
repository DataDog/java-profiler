---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-03 12:55:03 EST

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
| CPU Cores (start) | 43 |
| CPU Cores (end) | 39 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 62 |
| Sample Rate | 1.03/sec |
| Health Score | 64% |
| Threads | 9 |
| Allocations | 59 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 62 |
| Sample Rate | 1.03/sec |
| Health Score | 64% |
| Threads | 11 |
| Allocations | 41 |

<details>
<summary>CPU Timeline (5 unique values: 38-45 cores)</summary>

```
1793728253 43
1793728258 43
1793728263 43
1793728268 43
1793728273 43
1793728278 43
1793728283 43
1793728288 43
1793728293 45
1793728298 45
1793728303 45
1793728308 45
1793728313 45
1793728318 45
1793728323 45
1793728328 45
1793728333 45
1793728338 45
1793728343 45
1793728348 40
```
</details>

---

