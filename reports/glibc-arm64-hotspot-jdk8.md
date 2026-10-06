---
layout: default
title: glibc-arm64-hotspot-jdk8
---

## glibc-arm64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-10-06 11:23:36 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 38 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 89 |
| Sample Rate | 1.48/sec |
| Health Score | 92% |
| Threads | 10 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 174 |
| Sample Rate | 2.90/sec |
| Health Score | 181% |
| Threads | 12 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (5 unique values: 33-51 cores)</summary>

```
1791299943 38
1791299948 38
1791299953 33
1791299958 33
1791299963 33
1791299968 33
1791299973 33
1791299978 33
1791299983 41
1791299988 41
1791299993 46
1791299998 46
1791300003 46
1791300008 51
1791300013 51
1791300018 51
1791300023 51
1791300028 51
1791300033 51
1791300038 51
```
</details>

---

