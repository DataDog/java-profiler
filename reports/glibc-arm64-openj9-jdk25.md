---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-12 04:42:01 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 44 |
| CPU Cores (end) | 41 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 53 |
| Sample Rate | 0.88/sec |
| Health Score | 55% |
| Threads | 10 |
| Allocations | 65 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 57 |
| Sample Rate | 0.95/sec |
| Health Score | 59% |
| Threads | 12 |
| Allocations | 28 |

<details>
<summary>CPU Timeline (5 unique values: 41-45 cores)</summary>

```
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
1791794316 43
1791794321 43
1791794326 41
1791794331 41
```
</details>

---

