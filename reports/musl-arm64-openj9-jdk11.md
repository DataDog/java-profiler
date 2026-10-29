---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-29 13:49:37 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 46 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 262 |
| Sample Rate | 4.37/sec |
| Health Score | 273% |
| Threads | 9 |
| Allocations | 142 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 69 |
| Sample Rate | 1.15/sec |
| Health Score | 72% |
| Threads | 12 |
| Allocations | 50 |

<details>
<summary>CPU Timeline (4 unique values: 45-48 cores)</summary>

```
1793295795 46
1793295800 46
1793295805 46
1793295810 46
1793295815 46
1793295820 46
1793295825 46
1793295830 46
1793295835 46
1793295840 46
1793295845 46
1793295850 46
1793295855 45
1793295860 45
1793295865 45
1793295870 45
1793295875 45
1793295880 45
1793295885 45
1793295890 45
```
</details>

---

