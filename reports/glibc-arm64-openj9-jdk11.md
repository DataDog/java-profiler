---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-08-14 01:01:23 EDT

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
| CPU Samples | 121 |
| Sample Rate | 2.02/sec |
| Health Score | 126% |
| Threads | 11 |
| Allocations | 64 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 122 |
| Sample Rate | 2.03/sec |
| Health Score | 127% |
| Threads | 14 |
| Allocations | 64 |

<details>
<summary>CPU Timeline (2 unique values: 62-64 cores)</summary>

```
1786683323 64
1786683328 64
1786683333 64
1786683338 64
1786683343 64
1786683348 64
1786683353 64
1786683358 64
1786683363 64
1786683368 64
1786683373 64
1786683378 64
1786683384 62
1786683389 62
1786683394 62
1786683399 62
1786683404 62
1786683409 62
1786683414 62
1786683419 62
```
</details>

---

