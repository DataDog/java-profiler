---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-12 07:55:50 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 16 |
| CPU Cores (end) | 25 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 559 |
| Sample Rate | 9.32/sec |
| Health Score | 582% |
| Threads | 8 |
| Allocations | 370 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 726 |
| Sample Rate | 12.10/sec |
| Health Score | 756% |
| Threads | 10 |
| Allocations | 501 |

<details>
<summary>CPU Timeline (2 unique values: 16-25 cores)</summary>

```
1794487795 16
1794487800 16
1794487805 16
1794487810 16
1794487815 25
1794487820 25
1794487825 25
1794487830 25
1794487835 25
1794487840 25
1794487845 25
1794487850 25
1794487855 25
1794487860 25
1794487865 25
1794487870 25
1794487875 25
1794487880 25
1794487885 25
1794487890 25
```
</details>

---

