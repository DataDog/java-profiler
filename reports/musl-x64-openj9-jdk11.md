---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-25 07:51:11 EST

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
| CPU Cores (start) | 70 |
| CPU Cores (end) | 73 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 521 |
| Sample Rate | 8.68/sec |
| Health Score | 542% |
| Threads | 8 |
| Allocations | 396 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 685 |
| Sample Rate | 11.42/sec |
| Health Score | 714% |
| Threads | 8 |
| Allocations | 493 |

<details>
<summary>CPU Timeline (4 unique values: 47-73 cores)</summary>

```
1795610755 70
1795610760 70
1795610765 70
1795610770 70
1795610776 70
1795610781 70
1795610786 70
1795610791 47
1795610796 47
1795610801 47
1795610806 47
1795610811 47
1795610816 47
1795610821 64
1795610826 64
1795610831 64
1795610836 64
1795610841 64
1795610846 64
1795610851 64
```
</details>

---

