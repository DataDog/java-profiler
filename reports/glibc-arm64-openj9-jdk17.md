---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-10-12 04:42:01 EDT

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
| CPU Cores (start) | 47 |
| CPU Cores (end) | 41 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 340 |
| Sample Rate | 5.67/sec |
| Health Score | 354% |
| Threads | 8 |
| Allocations | 396 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 59 |
| Sample Rate | 0.98/sec |
| Health Score | 61% |
| Threads | 11 |
| Allocations | 74 |

<details>
<summary>CPU Timeline (6 unique values: 41-47 cores)</summary>

```
1791794216 47
1791794221 44
1791794226 44
1791794231 44
1791794236 44
1791794241 44
1791794246 44
1791794251 45
1791794256 45
1791794261 45
1791794266 45
1791794271 45
1791794276 45
1791794281 45
1791794286 43
1791794291 43
1791794296 42
1791794301 42
1791794306 42
1791794311 42
```
</details>

---

