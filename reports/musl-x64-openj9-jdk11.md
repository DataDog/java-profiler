---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-10 06:47:22 EST

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
| CPU Cores (start) | 73 |
| CPU Cores (end) | 70 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 535 |
| Sample Rate | 8.92/sec |
| Health Score | 557% |
| Threads | 8 |
| Allocations | 359 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 837 |
| Sample Rate | 13.95/sec |
| Health Score | 872% |
| Threads | 11 |
| Allocations | 533 |

<details>
<summary>CPU Timeline (3 unique values: 70-76 cores)</summary>

```
1794310961 73
1794310966 73
1794310971 73
1794310976 76
1794310981 76
1794310986 76
1794310991 70
1794310996 70
1794311001 70
1794311006 70
1794311011 70
1794311016 70
1794311021 70
1794311026 70
1794311031 70
1794311036 70
1794311041 70
1794311046 70
1794311051 70
1794311056 70
```
</details>

---

