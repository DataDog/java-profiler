---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-04-24 07:51:21 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 89 |
| CPU Cores (end) | 80 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 575 |
| Sample Rate | 9.58/sec |
| Health Score | 599% |
| Threads | 10 |
| Allocations | 366 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 703 |
| Sample Rate | 11.72/sec |
| Health Score | 732% |
| Threads | 11 |
| Allocations | 486 |

<details>
<summary>CPU Timeline (5 unique values: 79-89 cores)</summary>

```
1777031257 89
1777031262 79
1777031267 79
1777031272 79
1777031277 79
1777031282 79
1777031287 79
1777031292 79
1777031297 79
1777031302 85
1777031307 85
1777031312 85
1777031317 83
1777031322 83
1777031327 83
1777031332 83
1777031337 83
1777031342 83
1777031347 83
1777031352 83
```
</details>

---

