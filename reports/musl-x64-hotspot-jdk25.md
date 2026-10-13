---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-13 13:24:03 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 15 |
| CPU Cores (end) | 17 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 360 |
| Sample Rate | 6.00/sec |
| Health Score | 375% |
| Threads | 8 |
| Allocations | 373 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 492 |
| Sample Rate | 8.20/sec |
| Health Score | 512% |
| Threads | 9 |
| Allocations | 512 |

<details>
<summary>CPU Timeline (2 unique values: 15-17 cores)</summary>

```
1791911830 15
1791911835 15
1791911840 15
1791911845 15
1791911850 15
1791911855 15
1791911860 15
1791911865 15
1791911870 15
1791911875 15
1791911880 15
1791911885 15
1791911890 15
1791911895 15
1791911900 15
1791911905 15
1791911910 17
1791911915 17
1791911920 17
1791911926 17
```
</details>

---

