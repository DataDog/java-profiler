---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-11 17:16:29 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 31 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 354 |
| Sample Rate | 5.90/sec |
| Health Score | 369% |
| Threads | 9 |
| Allocations | 354 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 62 |
| Sample Rate | 1.03/sec |
| Health Score | 64% |
| Threads | 12 |
| Allocations | 49 |

<details>
<summary>CPU Timeline (5 unique values: 31-48 cores)</summary>

```
1794435108 48
1794435113 48
1794435118 48
1794435123 43
1794435128 43
1794435133 43
1794435138 43
1794435143 43
1794435148 43
1794435153 43
1794435158 43
1794435163 43
1794435168 38
1794435173 38
1794435178 38
1794435183 38
1794435188 38
1794435193 38
1794435198 38
1794435203 38
```
</details>

---

