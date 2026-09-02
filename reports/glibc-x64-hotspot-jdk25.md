---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-09-02 13:35:50 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk25 |
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
| CPU Samples | 501 |
| Sample Rate | 8.35/sec |
| Health Score | 522% |
| Threads | 9 |
| Allocations | 369 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 764 |
| Sample Rate | 12.73/sec |
| Health Score | 796% |
| Threads | 11 |
| Allocations | 457 |

<details>
<summary>CPU Timeline (3 unique values: 70-76 cores)</summary>

```
1788369952 76
1788369957 76
1788369962 76
1788369967 76
1788369972 76
1788369977 76
1788369982 76
1788369987 76
1788369992 76
1788369997 76
1788370002 76
1788370007 76
1788370012 76
1788370017 76
1788370022 76
1788370027 72
1788370032 72
1788370037 72
1788370042 72
1788370047 72
```
</details>

---

