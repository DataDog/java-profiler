---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-24 05:24:29 EDT

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
| CPU Cores (start) | 64 |
| CPU Cores (end) | 33 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 569 |
| Sample Rate | 9.48/sec |
| Health Score | 592% |
| Threads | 8 |
| Allocations | 377 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 863 |
| Sample Rate | 14.38/sec |
| Health Score | 899% |
| Threads | 9 |
| Allocations | 486 |

<details>
<summary>CPU Timeline (3 unique values: 32-64 cores)</summary>

```
1790241558 64
1790241563 64
1790241568 64
1790241573 64
1790241578 64
1790241583 64
1790241588 32
1790241593 32
1790241598 32
1790241603 32
1790241608 32
1790241613 32
1790241618 32
1790241623 32
1790241628 32
1790241633 32
1790241638 33
1790241643 33
1790241648 33
1790241653 33
```
</details>

---

