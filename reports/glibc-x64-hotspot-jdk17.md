---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-08-07 13:06:40 EDT

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
| CPU Cores (start) | 65 |
| CPU Cores (end) | 63 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 533 |
| Sample Rate | 8.88/sec |
| Health Score | 555% |
| Threads | 9 |
| Allocations | 338 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 634 |
| Sample Rate | 10.57/sec |
| Health Score | 661% |
| Threads | 10 |
| Allocations | 430 |

<details>
<summary>CPU Timeline (2 unique values: 63-65 cores)</summary>

```
1786122111 65
1786122116 65
1786122121 65
1786122126 65
1786122131 63
1786122136 63
1786122141 63
1786122146 63
1786122151 63
1786122156 63
1786122161 63
1786122166 63
1786122171 63
1786122176 63
1786122181 63
1786122186 63
1786122191 63
1786122196 63
1786122201 63
1786122206 63
```
</details>

---

