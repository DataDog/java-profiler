---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-02-12 13:12:34 EST

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
| CPU Cores (start) | 93 |
| CPU Cores (end) | 67 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 686 |
| Sample Rate | 11.43/sec |
| Health Score | 714% |
| Threads | 9 |
| Allocations | 375 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 697 |
| Sample Rate | 11.62/sec |
| Health Score | 726% |
| Threads | 10 |
| Allocations | 510 |

<details>
<summary>CPU Timeline (3 unique values: 67-93 cores)</summary>

```
1770919612 93
1770919617 93
1770919622 93
1770919627 93
1770919632 93
1770919637 84
1770919642 84
1770919647 84
1770919652 84
1770919657 84
1770919662 84
1770919667 84
1770919672 84
1770919677 84
1770919682 84
1770919687 84
1770919692 84
1770919697 84
1770919702 84
1770919707 84
```
</details>

---

