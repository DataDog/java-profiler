---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-22 09:44:14 EDT

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
| CPU Cores (start) | 78 |
| CPU Cores (end) | 78 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 621 |
| Sample Rate | 10.35/sec |
| Health Score | 647% |
| Threads | 9 |
| Allocations | 354 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 691 |
| Sample Rate | 11.52/sec |
| Health Score | 720% |
| Threads | 11 |
| Allocations | 454 |

<details>
<summary>CPU Timeline (3 unique values: 78-82 cores)</summary>

```
1792676377 78
1792676382 78
1792676387 78
1792676392 78
1792676397 78
1792676402 78
1792676407 78
1792676412 78
1792676417 80
1792676422 80
1792676427 82
1792676432 82
1792676437 82
1792676442 82
1792676447 82
1792676452 82
1792676457 82
1792676462 82
1792676467 82
1792676472 82
```
</details>

---

