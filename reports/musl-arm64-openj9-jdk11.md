---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-25 07:51:10 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 54 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 79 |
| Sample Rate | 1.32/sec |
| Health Score | 82% |
| Threads | 9 |
| Allocations | 51 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 63 |
| Sample Rate | 1.05/sec |
| Health Score | 66% |
| Threads | 13 |
| Allocations | 57 |

<details>
<summary>CPU Timeline (3 unique values: 54-64 cores)</summary>

```
1795610760 64
1795610765 64
1795610770 64
1795610775 64
1795610780 64
1795610785 64
1795610790 64
1795610795 64
1795610800 64
1795610805 64
1795610810 64
1795610815 64
1795610820 64
1795610825 64
1795610830 64
1795610835 64
1795610840 64
1795610845 59
1795610850 59
1795610855 59
```
</details>

---

