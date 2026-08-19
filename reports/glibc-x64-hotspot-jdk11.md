---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-08-19 11:16:47 EDT

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
| CPU Cores (start) | 83 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 510 |
| Sample Rate | 8.50/sec |
| Health Score | 531% |
| Threads | 8 |
| Allocations | 354 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 707 |
| Sample Rate | 11.78/sec |
| Health Score | 736% |
| Threads | 9 |
| Allocations | 457 |

<details>
<summary>CPU Timeline (3 unique values: 83-96 cores)</summary>

```
1787152155 83
1787152160 83
1787152165 83
1787152170 83
1787152175 83
1787152180 83
1787152185 91
1787152190 91
1787152195 91
1787152200 91
1787152205 91
1787152210 91
1787152215 91
1787152220 91
1787152225 91
1787152230 91
1787152235 96
1787152240 96
1787152245 96
1787152250 96
```
</details>

---

