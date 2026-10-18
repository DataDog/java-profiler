---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-18 01:04:35 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 16 |
| CPU Cores (end) | 16 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 51 |
| Sample Rate | 0.85/sec |
| Health Score | 53% |
| Threads | 10 |
| Allocations | 63 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 207 |
| Sample Rate | 3.45/sec |
| Health Score | 216% |
| Threads | 12 |
| Allocations | 117 |

<details>
<summary>CPU Timeline (1 unique values: 16-16 cores)</summary>

```
1792299627 16
1792299632 16
1792299637 16
1792299642 16
1792299647 16
1792299652 16
1792299657 16
1792299662 16
1792299667 16
1792299672 16
1792299677 16
1792299682 16
1792299687 16
1792299692 16
1792299697 16
1792299702 16
1792299707 16
1792299712 16
1792299717 16
1792299722 16
```
</details>

---

