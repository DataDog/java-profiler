---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-24 05:15:29 EST

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
| CPU Cores (start) | 45 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 571 |
| Sample Rate | 9.52/sec |
| Health Score | 595% |
| Threads | 9 |
| Allocations | 361 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 776 |
| Sample Rate | 12.93/sec |
| Health Score | 808% |
| Threads | 10 |
| Allocations | 477 |

<details>
<summary>CPU Timeline (4 unique values: 43-48 cores)</summary>

```
1795514968 45
1795514973 45
1795514978 43
1795514983 43
1795514988 43
1795514993 43
1795514998 43
1795515003 43
1795515008 43
1795515013 46
1795515018 46
1795515023 46
1795515028 46
1795515033 46
1795515038 46
1795515043 46
1795515048 46
1795515053 46
1795515058 46
1795515063 46
```
</details>

---

