---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-10 06:47:23 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 94 |
| CPU Cores (end) | 81 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 551 |
| Sample Rate | 9.18/sec |
| Health Score | 574% |
| Threads | 9 |
| Allocations | 373 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 686 |
| Sample Rate | 11.43/sec |
| Health Score | 714% |
| Threads | 11 |
| Allocations | 521 |

<details>
<summary>CPU Timeline (3 unique values: 87-94 cores)</summary>

```
1794310972 94
1794310977 90
1794310982 90
1794310987 90
1794310992 90
1794310997 90
1794311002 90
1794311008 90
1794311013 90
1794311018 90
1794311023 90
1794311028 90
1794311033 87
1794311038 87
1794311043 87
1794311048 87
1794311053 87
1794311058 87
1794311063 87
1794311068 87
```
</details>

---

