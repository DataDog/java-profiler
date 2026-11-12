---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-12 07:55:48 EST

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
| CPU Cores (start) | 85 |
| CPU Cores (end) | 80 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 473 |
| Sample Rate | 7.88/sec |
| Health Score | 492% |
| Threads | 8 |
| Allocations | 332 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 741 |
| Sample Rate | 12.35/sec |
| Health Score | 772% |
| Threads | 9 |
| Allocations | 462 |

<details>
<summary>CPU Timeline (3 unique values: 80-85 cores)</summary>

```
1794487826 85
1794487831 85
1794487836 82
1794487841 82
1794487846 82
1794487851 82
1794487856 82
1794487861 82
1794487866 82
1794487871 82
1794487876 82
1794487881 82
1794487886 82
1794487891 82
1794487896 82
1794487901 82
1794487906 82
1794487911 82
1794487916 82
1794487921 80
```
</details>

---

