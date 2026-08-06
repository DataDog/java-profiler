---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-08-06 07:56:21 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 82 |
| CPU Cores (end) | 86 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 531 |
| Sample Rate | 8.85/sec |
| Health Score | 553% |
| Threads | 9 |
| Allocations | 371 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 577 |
| Sample Rate | 9.62/sec |
| Health Score | 601% |
| Threads | 10 |
| Allocations | 439 |

<details>
<summary>CPU Timeline (4 unique values: 82-94 cores)</summary>

```
1786017131 82
1786017136 82
1786017141 82
1786017146 82
1786017151 82
1786017156 82
1786017161 82
1786017166 82
1786017171 82
1786017176 82
1786017181 82
1786017186 82
1786017191 89
1786017196 89
1786017201 89
1786017206 89
1786017211 89
1786017216 89
1786017221 94
1786017226 94
```
</details>

---

