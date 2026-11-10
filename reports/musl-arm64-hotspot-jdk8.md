---
layout: default
title: musl-arm64-hotspot-jdk8
---

## musl-arm64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-11-10 14:09:21 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 39 |
| CPU Cores (end) | 33 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 264 |
| Sample Rate | 4.40/sec |
| Health Score | 275% |
| Threads | 7 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 77 |
| Sample Rate | 1.28/sec |
| Health Score | 80% |
| Threads | 10 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (8 unique values: 30-46 cores)</summary>

```
1794337463 39
1794337468 39
1794337473 42
1794337478 42
1794337483 42
1794337488 42
1794337493 45
1794337498 45
1794337503 45
1794337508 46
1794337513 46
1794337518 34
1794337523 34
1794337528 33
1794337533 33
1794337538 30
1794337543 30
1794337548 31
1794337553 31
1794337558 33
```
</details>

---

