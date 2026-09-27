---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-27 05:47:45 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 59 |
| CPU Cores (end) | 68 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 522 |
| Sample Rate | 8.70/sec |
| Health Score | 544% |
| Threads | 8 |
| Allocations | 367 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 751 |
| Sample Rate | 12.52/sec |
| Health Score | 782% |
| Threads | 9 |
| Allocations | 562 |

<details>
<summary>CPU Timeline (2 unique values: 59-68 cores)</summary>

```
1790502204 59
1790502209 59
1790502214 59
1790502219 59
1790502224 59
1790502229 59
1790502234 59
1790502239 59
1790502244 59
1790502249 59
1790502254 59
1790502259 68
1790502264 68
1790502269 68
1790502274 68
1790502279 68
1790502284 68
1790502289 68
1790502294 68
1790502299 68
```
</details>

---

