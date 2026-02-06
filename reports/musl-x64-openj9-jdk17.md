---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-02-06 10:50:48 EST

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
| CPU Cores (start) | 70 |
| CPU Cores (end) | 68 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 598 |
| Sample Rate | 9.97/sec |
| Health Score | 623% |
| Threads | 10 |
| Allocations | 364 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 791 |
| Sample Rate | 13.18/sec |
| Health Score | 824% |
| Threads | 11 |
| Allocations | 421 |

<details>
<summary>CPU Timeline (2 unique values: 68-70 cores)</summary>

```
1770392677 70
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

