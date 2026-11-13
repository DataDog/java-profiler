---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-13 08:55:22 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 88 |
| CPU Cores (end) | 86 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 576 |
| Sample Rate | 9.60/sec |
| Health Score | 600% |
| Threads | 9 |
| Allocations | 358 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 743 |
| Sample Rate | 12.38/sec |
| Health Score | 774% |
| Threads | 11 |
| Allocations | 470 |

<details>
<summary>CPU Timeline (2 unique values: 86-88 cores)</summary>

```
1794577821 88
1794577826 88
1794577831 88
1794577836 86
1794577841 86
1794577846 86
1794577851 86
1794577856 86
1794577861 88
1794577866 88
1794577871 88
1794577876 88
1794577881 88
1794577886 88
1794577891 88
1794577896 88
1794577901 88
1794577906 88
1794577911 86
1794577916 86
```
</details>

---

