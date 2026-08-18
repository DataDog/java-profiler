---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-08-17 21:38:42 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk25 |
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
| CPU Samples | 75 |
| Sample Rate | 1.25/sec |
| Health Score | 78% |
| Threads | 9 |
| Allocations | 59 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 210 |
| Sample Rate | 3.50/sec |
| Health Score | 219% |
| Threads | 14 |
| Allocations | 57 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1787016834 48
1787016839 48
1787016844 48
1787016849 48
1787016854 43
1787016860 43
1787016865 43
1787016870 43
1787016875 43
1787016880 43
1787016885 43
1787016890 43
1787016895 43
1787016900 43
1787016905 48
1787016910 48
1787016915 48
1787016920 48
1787016925 48
1787016930 48
```
</details>

---

