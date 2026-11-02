---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-02 09:51:42 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 25 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 112 |
| Sample Rate | 1.87/sec |
| Health Score | 117% |
| Threads | 9 |
| Allocations | 78 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 94 |
| Sample Rate | 1.57/sec |
| Health Score | 98% |
| Threads | 11 |
| Allocations | 75 |

<details>
<summary>CPU Timeline (2 unique values: 25-30 cores)</summary>

```
1793630780 25
1793630785 25
1793630790 25
1793630795 25
1793630800 25
1793630805 25
1793630810 25
1793630815 25
1793630820 30
1793630825 30
1793630830 30
1793630835 30
1793630840 30
1793630845 30
1793630850 30
1793630855 30
1793630860 30
1793630865 30
1793630870 30
1793630875 30
```
</details>

---

