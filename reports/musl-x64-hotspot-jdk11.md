---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-10 14:09:21 EST

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
| CPU Cores (start) | 61 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 554 |
| Sample Rate | 9.23/sec |
| Health Score | 577% |
| Threads | 8 |
| Allocations | 369 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 801 |
| Sample Rate | 13.35/sec |
| Health Score | 834% |
| Threads | 9 |
| Allocations | 536 |

<details>
<summary>CPU Timeline (3 unique values: 61-64 cores)</summary>

```
1794337453 61
1794337458 61
1794337463 61
1794337468 61
1794337473 62
1794337478 62
1794337483 62
1794337488 62
1794337493 62
1794337498 62
1794337503 62
1794337508 62
1794337513 62
1794337518 64
1794337523 64
1794337528 64
1794337533 64
1794337538 64
1794337543 64
1794337548 64
```
</details>

---

