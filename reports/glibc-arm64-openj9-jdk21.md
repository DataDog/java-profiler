---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-09-21 15:32:20 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 8 |
| CPU Cores (end) | 7 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 48 |
| Sample Rate | 0.80/sec |
| Health Score | 50% |
| Threads | 9 |
| Allocations | 59 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 180 |
| Sample Rate | 3.00/sec |
| Health Score | 188% |
| Threads | 13 |
| Allocations | 163 |

<details>
<summary>CPU Timeline (2 unique values: 7-8 cores)</summary>

```
1790018826 8
1790018831 8
1790018836 8
1790018841 8
1790018846 8
1790018851 8
1790018856 8
1790018861 8
1790018866 8
1790018871 8
1790018876 8
1790018881 8
1790018886 8
1790018891 8
1790018896 8
1790018901 8
1790018906 8
1790018911 8
1790018916 8
1790018921 8
```
</details>

---

