---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-14 19:51:07 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
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
| CPU Samples | 83 |
| Sample Rate | 1.38/sec |
| Health Score | 86% |
| Threads | 11 |
| Allocations | 52 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 100 |
| Sample Rate | 1.67/sec |
| Health Score | 104% |
| Threads | 13 |
| Allocations | 71 |

<details>
<summary>CPU Timeline (2 unique values: 46-48 cores)</summary>

```
1794703631 46
1794703636 46
1794703641 46
1794703646 46
1794703651 48
1794703656 48
1794703661 48
1794703666 48
1794703671 48
1794703676 48
1794703681 48
1794703686 48
1794703691 48
1794703696 48
1794703701 48
1794703707 48
1794703712 48
1794703717 48
1794703722 48
1794703727 48
```
</details>

---

