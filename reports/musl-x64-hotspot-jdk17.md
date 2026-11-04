---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-04 16:24:56 EST

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
| CPU Cores (start) | 39 |
| CPU Cores (end) | 41 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 537 |
| Sample Rate | 8.95/sec |
| Health Score | 559% |
| Threads | 9 |
| Allocations | 381 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 571 |
| Sample Rate | 9.52/sec |
| Health Score | 595% |
| Threads | 10 |
| Allocations | 505 |

<details>
<summary>CPU Timeline (6 unique values: 37-46 cores)</summary>

```
1793827199 39
1793827204 37
1793827209 37
1793827214 37
1793827219 37
1793827224 37
1793827229 42
1793827234 42
1793827239 44
1793827244 44
1793827249 46
1793827254 46
1793827259 46
1793827264 46
1793827269 46
1793827274 46
1793827279 44
1793827284 44
1793827289 44
1793827294 44
```
</details>

---

