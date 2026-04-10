---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-04-10 19:29:56 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 68 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 550 |
| Sample Rate | 9.17/sec |
| Health Score | 573% |
| Threads | 9 |
| Allocations | 380 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 664 |
| Sample Rate | 11.07/sec |
| Health Score | 692% |
| Threads | 10 |
| Allocations | 501 |

<details>
<summary>CPU Timeline (2 unique values: 64-68 cores)</summary>

```
1775863626 68
1775863631 68
1775863636 68
1775863641 68
1775863646 68
1775863651 68
1775863656 68
1775863661 68
1775863666 68
1775863671 68
1775863676 68
1775863681 68
1775863686 68
1775863691 68
1775863696 68
1775863701 68
1775863706 68
1775863711 64
1775863716 64
1775863721 64
```
</details>

---

