---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-02 13:35:51 EDT

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
| CPU Cores (start) | 94 |
| CPU Cores (end) | 94 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 611 |
| Sample Rate | 10.18/sec |
| Health Score | 636% |
| Threads | 8 |
| Allocations | 364 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 837 |
| Sample Rate | 13.95/sec |
| Health Score | 872% |
| Threads | 12 |
| Allocations | 505 |

<details>
<summary>CPU Timeline (3 unique values: 92-96 cores)</summary>

```
1788369948 94
1788369953 92
1788369958 92
1788369963 92
1788369968 92
1788369973 94
1788369978 94
1788369983 94
1788369988 94
1788369993 94
1788369998 96
1788370003 96
1788370008 96
1788370013 96
1788370018 96
1788370023 96
1788370028 96
1788370033 96
1788370038 96
1788370043 94
```
</details>

---

