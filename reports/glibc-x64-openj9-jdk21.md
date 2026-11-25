---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-25 07:51:09 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 44 |
| CPU Cores (end) | 37 |
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
| Allocations | 368 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 601 |
| Sample Rate | 10.02/sec |
| Health Score | 626% |
| Threads | 11 |
| Allocations | 478 |

<details>
<summary>CPU Timeline (4 unique values: 37-47 cores)</summary>

```
1795610786 44
1795610791 44
1795610796 44
1795610801 44
1795610806 44
1795610811 44
1795610816 44
1795610821 44
1795610826 44
1795610831 44
1795610836 44
1795610841 42
1795610846 42
1795610851 42
1795610856 42
1795610861 42
1795610866 42
1795610871 42
1795610876 42
1795610881 42
```
</details>

---

