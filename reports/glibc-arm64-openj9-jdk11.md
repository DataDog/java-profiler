---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-04 05:50:49 EDT

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
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 71 |
| Sample Rate | 1.18/sec |
| Health Score | 74% |
| Threads | 11 |
| Allocations | 82 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 260 |
| Sample Rate | 4.33/sec |
| Health Score | 271% |
| Threads | 9 |
| Allocations | 120 |

<details>
<summary>CPU Timeline (2 unique values: 62-64 cores)</summary>

```
1788515206 64
1788515211 64
1788515216 64
1788515221 62
1788515226 62
1788515232 62
1788515237 62
1788515242 62
1788515247 62
1788515252 62
1788515257 62
1788515262 62
1788515267 62
1788515272 62
1788515277 62
1788515282 62
1788515287 62
1788515292 62
1788515297 62
1788515302 64
```
</details>

---

