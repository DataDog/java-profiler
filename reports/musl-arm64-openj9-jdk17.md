---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-09-17 16:47:41 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 14 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 549 |
| Sample Rate | 9.15/sec |
| Health Score | 572% |
| Threads | 9 |
| Allocations | 352 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 258 |
| Sample Rate | 4.30/sec |
| Health Score | 269% |
| Threads | 11 |
| Allocations | 117 |

<details>
<summary>CPU Timeline (2 unique values: 14-48 cores)</summary>

```
1789677771 48
1789677776 48
1789677781 48
1789677786 48
1789677791 48
1789677796 48
1789677801 14
1789677806 14
1789677811 14
1789677816 14
1789677821 14
1789677826 14
1789677831 14
1789677836 14
1789677841 14
1789677846 14
1789677851 14
1789677856 14
1789677861 14
1789677866 14
```
</details>

---

