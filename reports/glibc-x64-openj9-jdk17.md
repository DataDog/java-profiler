---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-10 16:27:32 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 62 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 430 |
| Sample Rate | 7.17/sec |
| Health Score | 448% |
| Threads | 9 |
| Allocations | 323 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 718 |
| Sample Rate | 11.97/sec |
| Health Score | 748% |
| Threads | 11 |
| Allocations | 447 |

<details>
<summary>CPU Timeline (5 unique values: 57-67 cores)</summary>

```
1794345676 64
1794345681 67
1794345686 67
1794345691 67
1794345696 59
1794345701 59
1794345706 59
1794345711 59
1794345716 57
1794345721 57
1794345726 57
1794345731 57
1794345736 60
1794345741 60
1794345746 60
1794345751 60
1794345756 60
1794345761 60
1794345766 60
1794345771 60
```
</details>

---

