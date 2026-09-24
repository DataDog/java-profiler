---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-23 20:34:28 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 57 |
| CPU Cores (end) | 25 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 496 |
| Sample Rate | 8.27/sec |
| Health Score | 517% |
| Threads | 8 |
| Allocations | 393 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 929 |
| Sample Rate | 15.48/sec |
| Health Score | 967% |
| Threads | 9 |
| Allocations | 519 |

<details>
<summary>CPU Timeline (3 unique values: 25-81 cores)</summary>

```
1790209795 57
1790209800 81
1790209805 81
1790209810 81
1790209815 81
1790209820 81
1790209825 81
1790209830 81
1790209835 81
1790209840 81
1790209845 81
1790209850 81
1790209855 81
1790209860 81
1790209865 81
1790209870 81
1790209875 81
1790209880 81
1790209885 81
1790209890 57
```
</details>

---

