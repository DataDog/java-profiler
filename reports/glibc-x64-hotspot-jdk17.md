---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-04-27 17:32:19 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 75 |
| CPU Cores (end) | 80 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 490 |
| Sample Rate | 8.17/sec |
| Health Score | 511% |
| Threads | 9 |
| Allocations | 354 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 973 |
| Sample Rate | 16.22/sec |
| Health Score | 1014% |
| Threads | 10 |
| Allocations | 447 |

<details>
<summary>CPU Timeline (3 unique values: 75-80 cores)</summary>

```
1777325224 75
1777325229 75
1777325234 75
1777325239 75
1777325244 79
1777325249 79
1777325254 79
1777325259 79
1777325264 79
1777325269 79
1777325274 79
1777325279 79
1777325284 79
1777325289 79
1777325294 80
1777325299 80
1777325304 80
1777325309 80
1777325314 80
1777325319 80
```
</details>

---

