---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-09-30 07:14:53 EDT

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
| CPU Cores (start) | 46 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 58 |
| Sample Rate | 0.97/sec |
| Health Score | 61% |
| Threads | 10 |
| Allocations | 51 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 66 |
| Sample Rate | 1.10/sec |
| Health Score | 69% |
| Threads | 13 |
| Allocations | 31 |

<details>
<summary>CPU Timeline (2 unique values: 46-48 cores)</summary>

```
1790766584 46
1790766589 46
1790766594 46
1790766599 46
1790766604 46
1790766609 46
1790766614 46
1790766619 46
1790766624 46
1790766629 46
1790766634 46
1790766639 46
1790766644 46
1790766649 46
1790766654 46
1790766659 46
1790766664 46
1790766669 48
1790766674 48
1790766679 48
```
</details>

---

