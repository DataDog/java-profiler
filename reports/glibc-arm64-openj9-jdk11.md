---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-11 05:29:41 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 29 |
| CPU Cores (end) | 34 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 131 |
| Sample Rate | 2.18/sec |
| Health Score | 136% |
| Threads | 8 |
| Allocations | 49 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 288 |
| Sample Rate | 4.80/sec |
| Health Score | 300% |
| Threads | 13 |
| Allocations | 147 |

<details>
<summary>CPU Timeline (2 unique values: 29-34 cores)</summary>

```
1794392614 29
1794392619 29
1794392624 29
1794392629 29
1794392634 29
1794392639 29
1794392644 34
1794392649 34
1794392654 34
1794392659 34
1794392664 34
1794392669 34
1794392674 34
1794392679 34
1794392684 34
1794392689 34
1794392694 34
1794392699 34
1794392704 34
1794392709 34
```
</details>

---

