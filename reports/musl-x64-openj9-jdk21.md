---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-09-23 10:27:24 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 56 |
| CPU Cores (end) | 72 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 512 |
| Sample Rate | 8.53/sec |
| Health Score | 533% |
| Threads | 9 |
| Allocations | 399 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 743 |
| Sample Rate | 12.38/sec |
| Health Score | 774% |
| Threads | 11 |
| Allocations | 521 |

<details>
<summary>CPU Timeline (4 unique values: 56-96 cores)</summary>

```
1790173229 56
1790173234 56
1790173239 56
1790173244 56
1790173249 56
1790173254 56
1790173259 56
1790173264 56
1790173269 56
1790173274 56
1790173279 56
1790173284 56
1790173289 56
1790173294 56
1790173299 56
1790173304 64
1790173309 64
1790173314 73
1790173319 73
1790173324 73
```
</details>

---

