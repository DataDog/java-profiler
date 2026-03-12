---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-03-12 11:39:22 EDT

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
| CPU Cores (start) | 72 |
| CPU Cores (end) | 86 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 494 |
| Sample Rate | 8.23/sec |
| Health Score | 514% |
| Threads | 11 |
| Allocations | 392 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 671 |
| Sample Rate | 11.18/sec |
| Health Score | 699% |
| Threads | 12 |
| Allocations | 506 |

<details>
<summary>CPU Timeline (6 unique values: 72-91 cores)</summary>

```
1773329596 72
1773329601 72
1773329606 76
1773329611 76
1773329616 76
1773329621 81
1773329626 81
1773329631 89
1773329636 89
1773329641 91
1773329646 91
1773329651 91
1773329656 91
1773329661 91
1773329666 91
1773329671 91
1773329676 91
1773329681 91
1773329686 91
1773329691 91
```
</details>

---

