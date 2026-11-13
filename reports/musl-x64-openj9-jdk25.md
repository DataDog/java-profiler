---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-13 10:22:23 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 29 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 592 |
| Sample Rate | 9.87/sec |
| Health Score | 617% |
| Threads | 8 |
| Allocations | 390 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 649 |
| Sample Rate | 10.82/sec |
| Health Score | 676% |
| Threads | 9 |
| Allocations | 526 |

<details>
<summary>CPU Timeline (3 unique values: 29-32 cores)</summary>

```
1794582900 29
1794582905 29
1794582910 29
1794582915 29
1794582920 32
1794582925 32
1794582930 30
1794582935 30
1794582940 30
1794582945 30
1794582950 30
1794582955 30
1794582960 30
1794582965 30
1794582970 30
1794582975 30
1794582980 30
1794582985 30
1794582990 30
1794582995 30
```
</details>

---

