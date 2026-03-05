---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-03-05 15:44:31 EST

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
| CPU Cores (start) | 84 |
| CPU Cores (end) | 82 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 438 |
| Sample Rate | 7.30/sec |
| Health Score | 456% |
| Threads | 11 |
| Allocations | 401 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 667 |
| Sample Rate | 11.12/sec |
| Health Score | 695% |
| Threads | 13 |
| Allocations | 528 |

<details>
<summary>CPU Timeline (2 unique values: 82-84 cores)</summary>

```
1772742910 84
1772742915 84
1772742920 84
1772742925 84
1772742930 84
1772742935 84
1772742940 84
1772742945 84
1772742950 84
1772742955 84
1772742960 82
1772742965 82
1772742970 82
1772742975 82
1772742980 82
1772742985 82
1772742990 82
1772742995 82
1772743000 82
1772743005 82
```
</details>

---

