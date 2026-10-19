---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-19 09:36:00 EDT

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
| CPU Cores (start) | 53 |
| CPU Cores (end) | 53 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 98 |
| Sample Rate | 1.63/sec |
| Health Score | 102% |
| Threads | 13 |
| Allocations | 58 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 310 |
| Sample Rate | 5.17/sec |
| Health Score | 323% |
| Threads | 13 |
| Allocations | 169 |

<details>
<summary>CPU Timeline (2 unique values: 48-53 cores)</summary>

```
1792416569 53
1792416574 53
1792416579 53
1792416584 53
1792416589 53
1792416594 48
1792416599 48
1792416604 48
1792416609 48
1792416614 48
1792416619 48
1792416624 48
1792416629 48
1792416634 48
1792416639 48
1792416644 48
1792416649 48
1792416654 48
1792416659 48
1792416664 48
```
</details>

---

