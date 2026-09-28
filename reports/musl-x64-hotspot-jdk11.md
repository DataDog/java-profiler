---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-28 10:34:17 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 70 |
| CPU Cores (end) | 79 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 517 |
| Sample Rate | 8.62/sec |
| Health Score | 539% |
| Threads | 8 |
| Allocations | 391 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 781 |
| Sample Rate | 13.02/sec |
| Health Score | 814% |
| Threads | 10 |
| Allocations | 467 |

<details>
<summary>CPU Timeline (5 unique values: 68-79 cores)</summary>

```
1790605752 70
1790605757 70
1790605762 70
1790605767 70
1790605772 70
1790605777 70
1790605782 70
1790605787 70
1790605792 70
1790605797 70
1790605802 68
1790605807 68
1790605812 68
1790605817 77
1790605822 77
1790605827 72
1790605832 72
1790605837 72
1790605842 72
1790605847 72
```
</details>

---

