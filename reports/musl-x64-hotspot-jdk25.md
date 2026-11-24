---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-24 11:51:15 EST

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
| CPU Cores (start) | 94 |
| CPU Cores (end) | 88 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 416 |
| Sample Rate | 6.93/sec |
| Health Score | 433% |
| Threads | 9 |
| Allocations | 412 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 587 |
| Sample Rate | 9.78/sec |
| Health Score | 611% |
| Threads | 12 |
| Allocations | 458 |

<details>
<summary>CPU Timeline (4 unique values: 88-94 cores)</summary>

```
1795538728 94
1795538733 94
1795538738 94
1795538743 94
1795538748 92
1795538753 92
1795538758 92
1795538763 92
1795538768 92
1795538773 92
1795538778 90
1795538783 90
1795538788 90
1795538793 90
1795538798 90
1795538803 90
1795538808 90
1795538813 88
1795538818 88
1795538823 88
```
</details>

---

