---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-20 12:23:33 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 59 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 576 |
| Sample Rate | 9.60/sec |
| Health Score | 600% |
| Threads | 9 |
| Allocations | 411 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 283 |
| Sample Rate | 4.72/sec |
| Health Score | 295% |
| Threads | 15 |
| Allocations | 154 |

<details>
<summary>CPU Timeline (2 unique values: 59-64 cores)</summary>

```
1795195214 64
1795195219 64
1795195224 59
1795195229 59
1795195234 59
1795195239 59
1795195244 59
1795195249 59
1795195254 59
1795195259 59
1795195264 59
1795195269 59
1795195274 59
1795195279 59
1795195284 59
1795195289 59
1795195294 64
1795195299 64
1795195304 64
1795195309 64
```
</details>

---

