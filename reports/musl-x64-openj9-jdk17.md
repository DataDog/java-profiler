---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-10 20:36:48 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 94 |
| CPU Cores (end) | 82 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 491 |
| Sample Rate | 8.18/sec |
| Health Score | 511% |
| Threads | 9 |
| Allocations | 411 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 635 |
| Sample Rate | 10.58/sec |
| Health Score | 661% |
| Threads | 10 |
| Allocations | 517 |

<details>
<summary>CPU Timeline (6 unique values: 73-94 cores)</summary>

```
1794360712 94
1794360717 85
1794360722 85
1794360727 78
1794360732 78
1794360737 78
1794360742 73
1794360747 73
1794360752 73
1794360757 73
1794360762 75
1794360767 75
1794360772 75
1794360777 75
1794360782 75
1794360787 75
1794360792 75
1794360797 75
1794360802 75
1794360807 75
```
</details>

---

