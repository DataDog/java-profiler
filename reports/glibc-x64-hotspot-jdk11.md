---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-21 04:46:07 EDT

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
| CPU Cores (start) | 51 |
| CPU Cores (end) | 44 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 537 |
| Sample Rate | 8.95/sec |
| Health Score | 559% |
| Threads | 8 |
| Allocations | 354 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 797 |
| Sample Rate | 13.28/sec |
| Health Score | 830% |
| Threads | 10 |
| Allocations | 496 |

<details>
<summary>CPU Timeline (4 unique values: 44-62 cores)</summary>

```
1789980033 51
1789980038 62
1789980043 62
1789980048 62
1789980053 62
1789980058 62
1789980063 62
1789980068 54
1789980073 54
1789980078 54
1789980083 54
1789980088 44
1789980093 44
1789980098 44
1789980103 44
1789980108 44
1789980113 44
1789980118 44
1789980123 44
1789980128 44
```
</details>

---

