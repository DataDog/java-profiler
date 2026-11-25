---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-25 07:51:08 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 33 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 512 |
| Sample Rate | 8.53/sec |
| Health Score | 533% |
| Threads | 9 |
| Allocations | 371 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 86 |
| Sample Rate | 1.43/sec |
| Health Score | 89% |
| Threads | 13 |
| Allocations | 58 |

<details>
<summary>CPU Timeline (2 unique values: 33-64 cores)</summary>

```
1795610781 33
1795610786 33
1795610791 33
1795610796 33
1795610801 33
1795610806 33
1795610811 33
1795610816 33
1795610821 33
1795610826 33
1795610831 33
1795610836 33
1795610841 33
1795610846 33
1795610851 33
1795610856 33
1795610861 33
1795610866 33
1795610871 33
1795610876 33
```
</details>

---

