---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-18 11:10:34 EDT

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
| CPU Cores (start) | 38 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 88 |
| Sample Rate | 1.47/sec |
| Health Score | 92% |
| Threads | 13 |
| Allocations | 63 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 114 |
| Sample Rate | 1.90/sec |
| Health Score | 119% |
| Threads | 14 |
| Allocations | 63 |

<details>
<summary>CPU Timeline (3 unique values: 38-48 cores)</summary>

```
1789743404 38
1789743409 38
1789743414 38
1789743419 38
1789743424 38
1789743429 38
1789743434 38
1789743439 38
1789743444 43
1789743449 43
1789743454 43
1789743459 43
1789743464 43
1789743469 43
1789743474 43
1789743480 43
1789743485 43
1789743490 43
1789743495 48
1789743500 48
```
</details>

---

