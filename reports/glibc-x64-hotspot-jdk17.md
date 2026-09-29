---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-09-29 09:12:05 EDT

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
| CPU Cores (start) | 40 |
| CPU Cores (end) | 65 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 517 |
| Sample Rate | 8.62/sec |
| Health Score | 539% |
| Threads | 9 |
| Allocations | 365 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 744 |
| Sample Rate | 12.40/sec |
| Health Score | 775% |
| Threads | 11 |
| Allocations | 430 |

<details>
<summary>CPU Timeline (3 unique values: 40-65 cores)</summary>

```
1790687094 40
1790687099 40
1790687104 40
1790687109 40
1790687114 40
1790687119 40
1790687124 48
1790687129 48
1790687134 48
1790687139 48
1790687144 48
1790687149 48
1790687154 48
1790687159 48
1790687164 65
1790687169 65
1790687174 65
1790687179 65
1790687184 65
1790687189 65
```
</details>

---

