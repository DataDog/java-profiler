---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-27 08:26:52 EST

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
| CPU Cores (start) | 73 |
| CPU Cores (end) | 75 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 116 |
| Sample Rate | 1.93/sec |
| Health Score | 121% |
| Threads | 10 |
| Allocations | 51 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 17 |
| Sample Rate | 0.28/sec |
| Health Score | 18% |
| Threads | 7 |
| Allocations | 17 |

<details>
<summary>CPU Timeline (4 unique values: 70-75 cores)</summary>

```
1795785637 73
1795785642 73
1795785647 73
1795785652 73
1795785657 73
1795785662 73
1795785667 73
1795785672 73
1795785677 73
1795785682 73
1795785687 73
1795785692 73
1795785697 73
1795785702 72
1795785707 72
1795785712 72
1795785717 70
1795785722 70
1795785727 70
1795785732 70
```
</details>

---

