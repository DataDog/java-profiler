---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-12 04:42:01 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk21 |
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
| CPU Samples | 390 |
| Sample Rate | 6.50/sec |
| Health Score | 406% |
| Threads | 9 |
| Allocations | 333 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 62 |
| Sample Rate | 1.03/sec |
| Health Score | 64% |
| Threads | 12 |
| Allocations | 51 |

<details>
<summary>CPU Timeline (5 unique values: 41-45 cores)</summary>

```
1791794232 44
1791794238 44
1791794243 44
1791794248 44
1791794253 45
1791794258 45
1791794263 45
1791794268 45
1791794273 45
1791794278 45
1791794283 43
1791794288 43
1791794293 42
1791794298 42
1791794303 42
1791794308 42
1791794313 43
1791794318 43
1791794323 43
1791794328 41
```
</details>

---

