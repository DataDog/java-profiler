---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-22 15:36:11 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk25 |
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
| CPU Samples | 80 |
| Sample Rate | 1.33/sec |
| Health Score | 83% |
| Threads | 9 |
| Allocations | 64 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 76 |
| Sample Rate | 1.27/sec |
| Health Score | 79% |
| Threads | 11 |
| Allocations | 52 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1795379548 64
1795379553 64
1795379558 64
1795379563 64
1795379568 64
1795379573 64
1795379578 64
1795379583 64
1795379588 64
1795379593 64
1795379598 64
1795379603 64
1795379608 64
1795379613 64
1795379618 64
1795379623 64
1795379628 64
1795379633 64
1795379638 64
1795379643 64
```
</details>

---

