---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-09-17 16:50:37 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 17 |
| CPU Cores (end) | 17 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 55 |
| Sample Rate | 0.92/sec |
| Health Score | 57% |
| Threads | 8 |
| Allocations | 62 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 178 |
| Sample Rate | 2.97/sec |
| Health Score | 186% |
| Threads | 14 |
| Allocations | 129 |

<details>
<summary>CPU Timeline (2 unique values: 12-17 cores)</summary>

```
1789677774 17
1789677779 12
1789677784 12
1789677789 12
1789677794 12
1789677799 12
1789677805 12
1789677810 12
1789677815 12
1789677820 12
1789677825 12
1789677830 12
1789677835 12
1789677840 12
1789677845 17
1789677850 17
1789677855 17
1789677860 17
1789677865 17
1789677870 17
```
</details>

---

