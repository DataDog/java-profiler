---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-17 09:39:57 EST

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
| CPU Cores (start) | 76 |
| CPU Cores (end) | 72 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 596 |
| Sample Rate | 9.93/sec |
| Health Score | 621% |
| Threads | 8 |
| Allocations | 390 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 991 |
| Sample Rate | 16.52/sec |
| Health Score | 1032% |
| Threads | 11 |
| Allocations | 547 |

<details>
<summary>CPU Timeline (3 unique values: 72-76 cores)</summary>

```
1794925993 76
1794925998 76
1794926003 76
1794926008 76
1794926013 76
1794926018 76
1794926023 74
1794926028 74
1794926033 74
1794926038 74
1794926043 74
1794926048 72
1794926053 72
1794926058 72
1794926063 72
1794926068 72
1794926073 72
1794926078 72
1794926083 72
1794926088 72
```
</details>

---

