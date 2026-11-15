---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-15 14:32:51 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 36 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 280 |
| Sample Rate | 4.67/sec |
| Health Score | 292% |
| Threads | 9 |
| Allocations | 181 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 92 |
| Sample Rate | 1.53/sec |
| Health Score | 96% |
| Threads | 12 |
| Allocations | 65 |

<details>
<summary>CPU Timeline (2 unique values: 36-48 cores)</summary>

```
1794770925 48
1794770930 48
1794770935 48
1794770940 48
1794770945 48
1794770950 48
1794770955 48
1794770960 48
1794770965 48
1794770970 48
1794770975 48
1794770980 48
1794770985 48
1794770990 48
1794770995 48
1794771000 48
1794771005 36
1794771010 36
1794771015 36
1794771020 36
```
</details>

---

