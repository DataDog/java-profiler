---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-09-23 09:48:43 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 59 |
| CPU Cores (end) | 60 |
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
| Allocations | 365 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 845 |
| Sample Rate | 14.08/sec |
| Health Score | 880% |
| Threads | 10 |
| Allocations | 448 |

<details>
<summary>CPU Timeline (5 unique values: 59-84 cores)</summary>

```
1790171056 59
1790171061 59
1790171066 59
1790171071 59
1790171076 84
1790171081 84
1790171086 84
1790171091 62
1790171096 62
1790171101 62
1790171106 62
1790171111 62
1790171116 62
1790171121 62
1790171126 62
1790171131 62
1790171136 62
1790171141 62
1790171146 62
1790171151 64
```
</details>

---

