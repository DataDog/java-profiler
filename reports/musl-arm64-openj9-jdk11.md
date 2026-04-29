---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-04-29 11:09:01 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 59 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 623 |
| Sample Rate | 10.38/sec |
| Health Score | 649% |
| Threads | 8 |
| Allocations | 408 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 42 |
| Sample Rate | 0.70/sec |
| Health Score | 44% |
| Threads | 10 |
| Allocations | 24 |

<details>
<summary>CPU Timeline (2 unique values: 59-64 cores)</summary>

```
1777475058 64
1777475063 64
1777475068 64
1777475073 64
1777475078 64
1777475083 64
1777475088 59
1777475093 59
1777475098 59
1777475103 59
1777475108 59
1777475113 59
1777475118 59
1777475123 59
1777475128 59
1777475134 59
1777475139 59
1777475144 59
1777475149 59
1777475154 59
```
</details>

---

