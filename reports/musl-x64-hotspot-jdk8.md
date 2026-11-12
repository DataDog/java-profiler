---
layout: default
title: musl-x64-hotspot-jdk8
---

## musl-x64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-11-12 07:47:09 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 76 |
| CPU Cores (end) | 90 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 399 |
| Sample Rate | 6.65/sec |
| Health Score | 416% |
| Threads | 9 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 175 |
| Sample Rate | 2.92/sec |
| Health Score | 182% |
| Threads | 8 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (3 unique values: 70-90 cores)</summary>

```
1794487338 76
1794487343 76
1794487348 76
1794487353 76
1794487358 70
1794487363 70
1794487368 70
1794487373 70
1794487378 70
1794487383 70
1794487388 70
1794487393 70
1794487398 70
1794487403 70
1794487408 70
1794487413 70
1794487418 70
1794487423 70
1794487428 90
1794487433 90
```
</details>

---

