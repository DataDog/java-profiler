---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-02 11:55:33 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 96 |
| CPU Cores (end) | 88 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 534 |
| Sample Rate | 8.90/sec |
| Health Score | 556% |
| Threads | 8 |
| Allocations | 358 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 746 |
| Sample Rate | 12.43/sec |
| Health Score | 777% |
| Threads | 10 |
| Allocations | 480 |

<details>
<summary>CPU Timeline (2 unique values: 88-96 cores)</summary>

```
1788364252 96
1788364257 96
1788364262 96
1788364267 96
1788364272 96
1788364277 96
1788364282 96
1788364287 96
1788364292 96
1788364297 96
1788364302 96
1788364307 96
1788364312 96
1788364317 96
1788364322 96
1788364327 96
1788364332 96
1788364337 96
1788364342 88
1788364347 88
```
</details>

---

