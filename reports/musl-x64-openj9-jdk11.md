---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-19 12:22:27 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 79 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 595 |
| Sample Rate | 9.92/sec |
| Health Score | 620% |
| Threads | 9 |
| Allocations | 415 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 776 |
| Sample Rate | 12.93/sec |
| Health Score | 808% |
| Threads | 10 |
| Allocations | 528 |

<details>
<summary>CPU Timeline (3 unique values: 79-96 cores)</summary>

```
1792426608 79
1792426613 79
1792426618 79
1792426623 79
1792426628 79
1792426633 79
1792426638 94
1792426643 94
1792426648 94
1792426653 94
1792426658 94
1792426663 94
1792426668 94
1792426673 96
1792426678 96
1792426683 96
1792426688 96
1792426693 96
1792426698 96
1792426704 96
```
</details>

---

