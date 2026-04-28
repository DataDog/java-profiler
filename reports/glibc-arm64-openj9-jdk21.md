---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-04-28 12:45:14 EDT

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
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 80 |
| Sample Rate | 1.33/sec |
| Health Score | 83% |
| Threads | 11 |
| Allocations | 70 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 687 |
| Sample Rate | 11.45/sec |
| Health Score | 716% |
| Threads | 10 |
| Allocations | 466 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1777394325 64
1777394330 64
1777394335 64
1777394340 64
1777394345 64
1777394350 64
1777394355 64
1777394360 64
1777394365 64
1777394370 64
1777394375 64
1777394380 64
1777394385 64
1777394390 64
1777394395 64
1777394400 64
1777394405 64
1777394410 64
1777394415 64
1777394420 64
```
</details>

---

