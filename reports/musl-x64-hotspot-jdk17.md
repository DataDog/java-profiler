---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-09-02 05:49:14 EDT

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
| CPU Cores (start) | 94 |
| CPU Cores (end) | 72 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 508 |
| Sample Rate | 8.47/sec |
| Health Score | 529% |
| Threads | 9 |
| Allocations | 376 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 771 |
| Sample Rate | 12.85/sec |
| Health Score | 803% |
| Threads | 11 |
| Allocations | 517 |

<details>
<summary>CPU Timeline (3 unique values: 72-94 cores)</summary>

```
1788342278 94
1788342283 94
1788342288 94
1788342293 94
1788342298 74
1788342303 74
1788342308 74
1788342313 74
1788342318 74
1788342323 74
1788342328 74
1788342333 74
1788342338 74
1788342343 74
1788342348 74
1788342353 74
1788342358 74
1788342363 74
1788342368 74
1788342373 74
```
</details>

---

