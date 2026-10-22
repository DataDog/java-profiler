---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-22 08:01:49 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 88 |
| CPU Cores (end) | 61 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 509 |
| Sample Rate | 8.48/sec |
| Health Score | 530% |
| Threads | 9 |
| Allocations | 374 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 601 |
| Sample Rate | 10.02/sec |
| Health Score | 626% |
| Threads | 10 |
| Allocations | 498 |

<details>
<summary>CPU Timeline (3 unique values: 61-96 cores)</summary>

```
1792670225 88
1792670230 88
1792670235 88
1792670240 96
1792670245 96
1792670250 96
1792670255 96
1792670260 96
1792670265 96
1792670270 96
1792670275 96
1792670280 96
1792670285 96
1792670290 96
1792670295 96
1792670300 96
1792670305 96
1792670310 96
1792670315 96
1792670320 61
```
</details>

---

