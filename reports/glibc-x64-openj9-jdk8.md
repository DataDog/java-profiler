---
layout: default
title: glibc-x64-openj9-jdk8
---

## glibc-x64-openj9-jdk8 - ✅ PASS

**Date:** 2026-11-10 10:56:50 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 62 |
| CPU Cores (end) | 53 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 380 |
| Sample Rate | 6.33/sec |
| Health Score | 396% |
| Threads | 7 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 162 |
| Sample Rate | 2.70/sec |
| Health Score | 169% |
| Threads | 6 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (6 unique values: 52-74 cores)</summary>

```
1794325894 62
1794325900 62
1794325905 62
1794325910 74
1794325915 74
1794325920 54
1794325925 54
1794325930 54
1794325935 54
1794325940 54
1794325945 54
1794325950 54
1794325955 54
1794325960 52
1794325965 52
1794325970 52
1794325975 55
1794325980 55
1794325985 53
1794325990 53
```
</details>

---

