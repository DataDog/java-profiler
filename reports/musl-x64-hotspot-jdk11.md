---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-29 14:36:23 EDT

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
| CPU Cores (start) | 57 |
| CPU Cores (end) | 62 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 656 |
| Sample Rate | 10.93/sec |
| Health Score | 683% |
| Threads | 8 |
| Allocations | 377 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 750 |
| Sample Rate | 12.50/sec |
| Health Score | 781% |
| Threads | 9 |
| Allocations | 574 |

<details>
<summary>CPU Timeline (3 unique values: 57-62 cores)</summary>

```
1790706511 57
1790706516 57
1790706521 57
1790706526 57
1790706531 57
1790706536 60
1790706541 60
1790706546 60
1790706551 60
1790706556 60
1790706561 60
1790706566 60
1790706571 60
1790706576 60
1790706581 60
1790706586 60
1790706591 60
1790706596 60
1790706601 60
1790706606 60
```
</details>

---

