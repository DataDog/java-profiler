---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-15 03:56:31 EDT

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
| CPU Cores (start) | 30 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 621 |
| Sample Rate | 10.35/sec |
| Health Score | 647% |
| Threads | 8 |
| Allocations | 400 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 640 |
| Sample Rate | 10.67/sec |
| Health Score | 667% |
| Threads | 10 |
| Allocations | 451 |

<details>
<summary>CPU Timeline (3 unique values: 28-32 cores)</summary>

```
1792050685 30
1792050690 30
1792050695 30
1792050700 30
1792050705 30
1792050710 30
1792050715 30
1792050720 30
1792050725 30
1792050730 30
1792050735 30
1792050740 30
1792050745 28
1792050751 28
1792050756 28
1792050761 28
1792050766 28
1792050771 28
1792050776 28
1792050781 28
```
</details>

---

