---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-05-12 03:36:04 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 41 |
| CPU Cores (end) | 71 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 495 |
| Sample Rate | 8.25/sec |
| Health Score | 516% |
| Threads | 9 |
| Allocations | 391 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 605 |
| Sample Rate | 10.08/sec |
| Health Score | 630% |
| Threads | 10 |
| Allocations | 510 |

<details>
<summary>CPU Timeline (5 unique values: 38-71 cores)</summary>

```
1778571121 41
1778571126 41
1778571131 41
1778571136 41
1778571141 41
1778571146 41
1778571151 41
1778571156 41
1778571161 41
1778571166 41
1778571171 63
1778571176 63
1778571181 63
1778571186 63
1778571191 43
1778571196 43
1778571201 43
1778571206 43
1778571211 38
1778571216 38
```
</details>

---

