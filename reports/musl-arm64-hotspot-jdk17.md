---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-10-08 09:47:45 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 51 |
| CPU Cores (end) | 41 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 78 |
| Sample Rate | 1.30/sec |
| Health Score | 81% |
| Threads | 10 |
| Allocations | 76 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 17 |
| Sample Rate | 0.28/sec |
| Health Score | 18% |
| Threads | 7 |
| Allocations | 22 |

<details>
<summary>CPU Timeline (3 unique values: 41-51 cores)</summary>

```
1791466867 51
1791466872 51
1791466877 51
1791466882 51
1791466887 51
1791466892 46
1791466897 46
1791466902 46
1791466907 46
1791466912 46
1791466917 46
1791466922 46
1791466927 46
1791466932 46
1791466937 46
1791466942 46
1791466947 46
1791466952 46
1791466957 46
1791466962 46
```
</details>

---

