---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-09 16:19:02 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 51 |
| CPU Cores (end) | 55 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 602 |
| Sample Rate | 10.03/sec |
| Health Score | 627% |
| Threads | 9 |
| Allocations | 381 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 880 |
| Sample Rate | 14.67/sec |
| Health Score | 917% |
| Threads | 11 |
| Allocations | 481 |

<details>
<summary>CPU Timeline (4 unique values: 48-55 cores)</summary>

```
1794258908 51
1794258913 51
1794258918 51
1794258923 51
1794258928 51
1794258933 51
1794258938 48
1794258943 48
1794258948 48
1794258953 48
1794258958 48
1794258963 48
1794258968 48
1794258973 48
1794258978 48
1794258983 48
1794258988 48
1794258993 53
1794258998 53
1794259003 53
```
</details>

---

