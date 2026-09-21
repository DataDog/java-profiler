---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-09-21 15:32:21 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 53 |
| CPU Cores (end) | 57 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 529 |
| Sample Rate | 8.82/sec |
| Health Score | 551% |
| Threads | 9 |
| Allocations | 362 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 712 |
| Sample Rate | 11.87/sec |
| Health Score | 742% |
| Threads | 11 |
| Allocations | 440 |

<details>
<summary>CPU Timeline (4 unique values: 47-57 cores)</summary>

```
1790018821 53
1790018826 53
1790018831 53
1790018836 53
1790018841 53
1790018846 53
1790018851 55
1790018856 55
1790018861 47
1790018866 47
1790018871 47
1790018876 47
1790018881 47
1790018886 47
1790018891 47
1790018896 47
1790018901 47
1790018906 47
1790018911 47
1790018916 47
```
</details>

---

