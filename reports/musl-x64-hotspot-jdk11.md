---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-28 07:48:56 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 29 |
| CPU Cores (end) | 11 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 571 |
| Sample Rate | 9.52/sec |
| Health Score | 595% |
| Threads | 8 |
| Allocations | 390 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 678 |
| Sample Rate | 11.30/sec |
| Health Score | 706% |
| Threads | 9 |
| Allocations | 524 |

<details>
<summary>CPU Timeline (2 unique values: 11-29 cores)</summary>

```
1793187861 29
1793187866 11
1793187871 11
1793187876 11
1793187881 11
1793187886 11
1793187891 11
1793187896 11
1793187901 11
1793187906 11
1793187911 11
1793187916 11
1793187921 11
1793187926 11
1793187931 11
1793187936 11
1793187941 11
1793187946 11
1793187951 11
1793187956 11
```
</details>

---

