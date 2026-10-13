---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-10-13 13:24:03 EDT

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
| CPU Cores (start) | 92 |
| CPU Cores (end) | 66 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 539 |
| Sample Rate | 8.98/sec |
| Health Score | 561% |
| Threads | 9 |
| Allocations | 387 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 818 |
| Sample Rate | 13.63/sec |
| Health Score | 852% |
| Threads | 11 |
| Allocations | 478 |

<details>
<summary>CPU Timeline (4 unique values: 66-92 cores)</summary>

```
1791911855 92
1791911860 92
1791911865 92
1791911870 92
1791911875 92
1791911880 92
1791911885 88
1791911890 88
1791911895 88
1791911900 88
1791911905 88
1791911910 88
1791911915 88
1791911920 88
1791911925 88
1791911930 88
1791911935 68
1791911940 68
1791911945 68
1791911950 66
```
</details>

---

