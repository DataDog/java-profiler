---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-18 13:18:40 EST

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
| CPU Cores (start) | 81 |
| CPU Cores (end) | 76 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 608 |
| Sample Rate | 10.13/sec |
| Health Score | 633% |
| Threads | 8 |
| Allocations | 391 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 981 |
| Sample Rate | 16.35/sec |
| Health Score | 1022% |
| Threads | 9 |
| Allocations | 512 |

<details>
<summary>CPU Timeline (3 unique values: 76-81 cores)</summary>

```
1795025688 81
1795025693 81
1795025698 81
1795025703 81
1795025708 81
1795025713 81
1795025718 81
1795025723 81
1795025728 81
1795025733 78
1795025738 78
1795025743 78
1795025748 78
1795025753 78
1795025758 78
1795025763 78
1795025768 78
1795025773 78
1795025778 78
1795025783 78
```
</details>

---

