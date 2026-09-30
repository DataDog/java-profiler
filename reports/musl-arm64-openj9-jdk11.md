---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-30 07:14:54 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 42 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 379 |
| Sample Rate | 6.32/sec |
| Health Score | 395% |
| Threads | 11 |
| Allocations | 184 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 28 |
| Sample Rate | 0.47/sec |
| Health Score | 29% |
| Threads | 8 |
| Allocations | 17 |

<details>
<summary>CPU Timeline (2 unique values: 42-46 cores)</summary>

```
1790766589 42
1790766594 42
1790766599 42
1790766604 42
1790766609 42
1790766614 42
1790766619 42
1790766624 42
1790766629 42
1790766634 42
1790766639 42
1790766644 46
1790766649 46
1790766654 46
1790766659 46
1790766664 46
1790766669 46
1790766674 46
1790766679 46
1790766684 46
```
</details>

---

