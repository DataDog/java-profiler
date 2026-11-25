---
layout: default
title: glibc-arm64-openj9-jdk8
---

## glibc-arm64-openj9-jdk8 - ✅ PASS

**Date:** 2026-11-25 07:51:08 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 59 |
| CPU Cores (end) | 60 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 55 |
| Sample Rate | 0.92/sec |
| Health Score | 57% |
| Threads | 8 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 77 |
| Sample Rate | 1.28/sec |
| Health Score | 80% |
| Threads | 14 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (3 unique values: 55-60 cores)</summary>

```
1795610781 59
1795610786 59
1795610791 59
1795610796 59
1795610801 55
1795610806 55
1795610811 55
1795610816 55
1795610821 55
1795610826 55
1795610831 60
1795610836 60
1795610841 60
1795610846 60
1795610851 60
1795610856 60
1795610861 60
1795610866 60
1795610871 60
1795610876 60
```
</details>

---

