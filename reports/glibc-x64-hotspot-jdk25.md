---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-25 08:52:57 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 56 |
| CPU Cores (end) | 56 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 93 |
| Sample Rate | 1.55/sec |
| Health Score | 97% |
| Threads | 9 |
| Allocations | 59 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 15 |
| Sample Rate | 0.25/sec |
| Health Score | 16% |
| Threads | 7 |
| Allocations | 3 |

<details>
<summary>CPU Timeline (2 unique values: 56-58 cores)</summary>

```
1795614511 56
1795614516 56
1795614521 56
1795614526 56
1795614531 56
1795614536 56
1795614541 56
1795614546 56
1795614551 56
1795614556 56
1795614561 56
1795614566 56
1795614571 56
1795614576 56
1795614581 56
1795614586 56
1795614591 56
1795614596 58
1795614601 58
1795614606 58
```
</details>

---

