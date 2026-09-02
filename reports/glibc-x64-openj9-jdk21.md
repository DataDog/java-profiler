---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-09-02 14:43:42 EDT

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
| CPU Cores (start) | 91 |
| CPU Cores (end) | 88 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 518 |
| Sample Rate | 8.63/sec |
| Health Score | 539% |
| Threads | 9 |
| Allocations | 339 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 590 |
| Sample Rate | 9.83/sec |
| Health Score | 614% |
| Threads | 10 |
| Allocations | 428 |

<details>
<summary>CPU Timeline (3 unique values: 88-96 cores)</summary>

```
1788374364 91
1788374369 91
1788374374 91
1788374379 91
1788374384 91
1788374389 91
1788374394 91
1788374399 91
1788374404 91
1788374409 91
1788374414 91
1788374419 91
1788374424 91
1788374429 96
1788374434 96
1788374439 96
1788374444 96
1788374449 96
1788374454 88
1788374459 88
```
</details>

---

