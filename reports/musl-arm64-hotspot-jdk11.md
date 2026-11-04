---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-04 15:01:25 EST

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
| CPU Cores (start) | 43 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 84 |
| Sample Rate | 1.40/sec |
| Health Score | 87% |
| Threads | 9 |
| Allocations | 61 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 70 |
| Sample Rate | 1.17/sec |
| Health Score | 73% |
| Threads | 11 |
| Allocations | 33 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1793822209 43
1793822214 43
1793822219 43
1793822224 43
1793822229 43
1793822234 43
1793822239 43
1793822244 43
1793822249 43
1793822254 48
1793822259 48
1793822264 48
1793822269 48
1793822274 48
1793822279 43
1793822284 43
1793822289 43
1793822294 43
1793822299 43
1793822304 43
```
</details>

---

