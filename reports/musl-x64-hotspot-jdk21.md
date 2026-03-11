---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-03-11 10:07:44 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 84 |
| CPU Cores (end) | 90 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 706 |
| Sample Rate | 11.77/sec |
| Health Score | 736% |
| Threads | 10 |
| Allocations | 391 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 778 |
| Sample Rate | 12.97/sec |
| Health Score | 811% |
| Threads | 12 |
| Allocations | 474 |

<details>
<summary>CPU Timeline (6 unique values: 84-92 cores)</summary>

```
1773237468 84
1773237473 84
1773237478 84
1773237483 85
1773237488 85
1773237493 85
1773237498 86
1773237503 86
1773237508 86
1773237513 88
1773237518 88
1773237523 88
1773237528 92
1773237533 92
1773237538 92
1773237543 92
1773237548 92
1773237553 92
1773237558 92
1773237563 91
```
</details>

---

