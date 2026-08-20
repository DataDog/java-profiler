---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-08-20 05:42:38 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 47 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 388 |
| Sample Rate | 6.47/sec |
| Health Score | 404% |
| Threads | 9 |
| Allocations | 374 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 54 |
| Sample Rate | 0.90/sec |
| Health Score | 56% |
| Threads | 14 |
| Allocations | 35 |

<details>
<summary>CPU Timeline (3 unique values: 46-48 cores)</summary>

```
1787218634 47
1787218639 47
1787218644 47
1787218649 47
1787218654 48
1787218659 48
1787218664 48
1787218669 48
1787218674 48
1787218679 48
1787218684 46
1787218689 46
1787218694 46
1787218699 46
1787218704 46
1787218709 46
1787218714 46
1787218719 46
1787218724 46
1787218729 46
```
</details>

---

