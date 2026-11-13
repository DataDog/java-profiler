---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-13 12:19:03 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 22 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 60 |
| Sample Rate | 1.00/sec |
| Health Score | 62% |
| Threads | 11 |
| Allocations | 67 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 253 |
| Sample Rate | 4.22/sec |
| Health Score | 264% |
| Threads | 13 |
| Allocations | 130 |

<details>
<summary>CPU Timeline (5 unique values: 22-48 cores)</summary>

```
1794590105 48
1794590110 48
1794590115 48
1794590120 40
1794590125 40
1794590130 40
1794590135 40
1794590140 40
1794590145 40
1794590150 40
1794590155 40
1794590160 40
1794590165 40
1794590170 40
1794590175 40
1794590180 40
1794590186 40
1794590191 40
1794590196 40
1794590201 39
```
</details>

---

