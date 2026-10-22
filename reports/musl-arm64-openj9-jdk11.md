---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-22 18:25:51 EDT

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 96 |
| Sample Rate | 1.60/sec |
| Health Score | 100% |
| Threads | 9 |
| Allocations | 74 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 457 |
| Sample Rate | 7.62/sec |
| Health Score | 476% |
| Threads | 13 |
| Allocations | 156 |

<details>
<summary>CPU Timeline (1 unique values: 48-48 cores)</summary>

```
1792707664 48
1792707669 48
1792707674 48
1792707679 48
1792707684 48
1792707689 48
1792707694 48
1792707699 48
1792707704 48
1792707709 48
1792707714 48
1792707719 48
1792707725 48
1792707730 48
1792707735 48
1792707740 48
1792707745 48
1792707750 48
1792707755 48
1792707760 48
```
</details>

---

