---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-09-02 13:35:52 EDT

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
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 582 |
| Sample Rate | 9.70/sec |
| Health Score | 606% |
| Threads | 9 |
| Allocations | 343 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 627 |
| Sample Rate | 10.45/sec |
| Health Score | 653% |
| Threads | 9 |
| Allocations | 515 |

<details>
<summary>CPU Timeline (2 unique values: 94-96 cores)</summary>

```
1788369947 94
1788369952 94
1788369957 94
1788369962 94
1788369967 96
1788369972 96
1788369977 96
1788369982 96
1788369987 96
1788369992 96
1788369997 96
1788370002 96
1788370007 96
1788370012 96
1788370017 96
1788370022 96
1788370027 96
1788370032 96
1788370037 96
1788370042 94
```
</details>

---

