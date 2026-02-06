---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-02-06 10:50:47 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 72 |
| CPU Cores (end) | 68 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 501 |
| Sample Rate | 8.35/sec |
| Health Score | 522% |
| Threads | 10 |
| Allocations | 413 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 762 |
| Sample Rate | 12.70/sec |
| Health Score | 794% |
| Threads | 12 |
| Allocations | 481 |

<details>
<summary>CPU Timeline (3 unique values: 68-72 cores)</summary>

```
1770392677 72
1770392682 70
1770392687 70
1770392692 70
1770392697 70
1770392702 70
1770392707 70
1770392712 70
1770392717 70
1770392722 70
1770392727 70
1770392732 70
1770392737 70
1770392742 70
1770392747 70
1770392752 68
1770392757 68
1770392762 68
1770392767 68
1770392772 68
```
</details>

---

