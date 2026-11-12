---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-12 05:47:36 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 40 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 68 |
| Sample Rate | 1.13/sec |
| Health Score | 71% |
| Threads | 9 |
| Allocations | 66 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 608 |
| Sample Rate | 10.13/sec |
| Health Score | 633% |
| Threads | 9 |
| Allocations | 479 |

<details>
<summary>CPU Timeline (6 unique values: 40-48 cores)</summary>

```
1794480183 40
1794480188 40
1794480193 40
1794480198 44
1794480203 44
1794480208 43
1794480213 43
1794480218 47
1794480223 47
1794480228 48
1794480233 48
1794480238 48
1794480243 48
1794480248 48
1794480253 48
1794480258 48
1794480263 46
1794480268 46
1794480273 46
1794480278 46
```
</details>

---

