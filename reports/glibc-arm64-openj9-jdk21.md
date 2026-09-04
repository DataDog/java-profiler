---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-09-04 05:50:49 EDT

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
| CPU Samples | 379 |
| Sample Rate | 6.32/sec |
| Health Score | 395% |
| Threads | 9 |
| Allocations | 377 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 70 |
| Sample Rate | 1.17/sec |
| Health Score | 73% |
| Threads | 10 |
| Allocations | 40 |

<details>
<summary>CPU Timeline (2 unique values: 62-64 cores)</summary>

```
1788515195 64
1788515200 64
1788515205 64
1788515210 64
1788515215 64
1788515220 62
1788515225 62
1788515230 62
1788515235 62
1788515240 62
1788515245 62
1788515250 62
1788515255 62
1788515260 62
1788515265 62
1788515270 62
1788515275 62
1788515280 62
1788515285 62
1788515290 62
```
</details>

---

