---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-02-05 05:23:34 EST

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
| CPU Cores (start) | 30 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 571 |
| Sample Rate | 9.52/sec |
| Health Score | 595% |
| Threads | 8 |
| Allocations | 357 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 968 |
| Sample Rate | 16.13/sec |
| Health Score | 1008% |
| Threads | 9 |
| Allocations | 479 |

<details>
<summary>CPU Timeline (2 unique values: 30-32 cores)</summary>

```
1770286796 30
1770286801 30
1770286806 32
1770286811 32
1770286816 32
1770286821 32
1770286826 32
1770286831 32
1770286836 32
1770286841 32
1770286846 32
1770286851 32
1770286856 32
1770286861 32
1770286866 32
1770286871 32
1770286876 32
1770286881 32
1770286886 32
1770286891 32
```
</details>

---

