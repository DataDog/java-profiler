---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-02-03 10:07:26 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 84 |
| CPU Cores (end) | 90 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 667 |
| Sample Rate | 11.12/sec |
| Health Score | 695% |
| Threads | 8 |
| Allocations | 374 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 891 |
| Sample Rate | 14.85/sec |
| Health Score | 928% |
| Threads | 9 |
| Allocations | 478 |

<details>
<summary>CPU Timeline (3 unique values: 78-90 cores)</summary>

```
1770130826 84
1770130831 84
1770130836 84
1770130841 84
1770130846 84
1770130851 84
1770130856 84
1770130861 84
1770130866 84
1770130871 84
1770130876 84
1770130881 84
1770130886 84
1770130891 84
1770130896 78
1770130901 78
1770130906 78
1770130911 78
1770130916 78
1770130921 78
```
</details>

---

