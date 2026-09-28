---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-09-28 06:45:42 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 65 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 471 |
| Sample Rate | 7.85/sec |
| Health Score | 491% |
| Threads | 9 |
| Allocations | 359 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 612 |
| Sample Rate | 10.20/sec |
| Health Score | 637% |
| Threads | 11 |
| Allocations | 469 |

<details>
<summary>CPU Timeline (5 unique values: 44-65 cores)</summary>

```
1790592128 65
1790592133 65
1790592138 65
1790592143 45
1790592148 45
1790592153 45
1790592158 45
1790592163 45
1790592168 45
1790592173 45
1790592178 45
1790592183 45
1790592188 45
1790592193 45
1790592198 60
1790592203 60
1790592208 44
1790592213 44
1790592218 48
1790592223 48
```
</details>

---

