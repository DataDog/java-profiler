---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-09-17 15:35:22 EDT

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
| CPU Cores (start) | 76 |
| CPU Cores (end) | 81 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 629 |
| Sample Rate | 10.48/sec |
| Health Score | 655% |
| Threads | 9 |
| Allocations | 366 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 614 |
| Sample Rate | 10.23/sec |
| Health Score | 639% |
| Threads | 10 |
| Allocations | 452 |

<details>
<summary>CPU Timeline (3 unique values: 76-81 cores)</summary>

```
1789673389 76
1789673394 76
1789673399 76
1789673404 76
1789673409 76
1789673414 76
1789673419 76
1789673424 76
1789673429 76
1789673434 76
1789673439 80
1789673444 80
1789673449 80
1789673454 80
1789673459 80
1789673464 80
1789673469 80
1789673474 80
1789673479 80
1789673484 80
```
</details>

---

