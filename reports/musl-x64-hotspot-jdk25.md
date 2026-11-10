---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-10 14:09:21 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk25 |
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
| CPU Samples | 466 |
| Sample Rate | 7.77/sec |
| Health Score | 486% |
| Threads | 9 |
| Allocations | 388 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 682 |
| Sample Rate | 11.37/sec |
| Health Score | 711% |
| Threads | 9 |
| Allocations | 538 |

<details>
<summary>CPU Timeline (4 unique values: 39-49 cores)</summary>

```
1794337463 39
1794337468 39
1794337473 39
1794337478 39
1794337483 39
1794337488 39
1794337493 39
1794337498 42
1794337503 42
1794337508 42
1794337513 42
1794337518 42
1794337523 42
1794337528 42
1794337533 42
1794337538 42
1794337543 42
1794337548 42
1794337553 49
1794337558 49
```
</details>

---

