---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-05 05:59:39 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 52 |
| CPU Cores (end) | 55 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 540 |
| Sample Rate | 9.00/sec |
| Health Score | 562% |
| Threads | 8 |
| Allocations | 365 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 763 |
| Sample Rate | 12.72/sec |
| Health Score | 795% |
| Threads | 10 |
| Allocations | 472 |

<details>
<summary>CPU Timeline (5 unique values: 51-55 cores)</summary>

```
1793876018 52
1793876023 52
1793876028 52
1793876033 52
1793876038 52
1793876043 52
1793876048 52
1793876053 52
1793876058 54
1793876063 54
1793876068 51
1793876073 51
1793876078 51
1793876083 51
1793876088 51
1793876093 51
1793876098 53
1793876103 53
1793876108 53
1793876113 53
```
</details>

---

