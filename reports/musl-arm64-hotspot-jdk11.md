---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-26 20:50:46 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 59 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 114 |
| Sample Rate | 1.90/sec |
| Health Score | 119% |
| Threads | 8 |
| Allocations | 75 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 26 |
| Sample Rate | 0.43/sec |
| Health Score | 27% |
| Threads | 7 |
| Allocations | 27 |

<details>
<summary>CPU Timeline (2 unique values: 59-64 cores)</summary>

```
1793061951 59
1793061956 59
1793061961 59
1793061966 59
1793061971 59
1793061976 59
1793061981 59
1793061986 59
1793061991 59
1793061996 59
1793062001 59
1793062006 59
1793062011 59
1793062016 59
1793062021 59
1793062026 59
1793062031 59
1793062036 64
1793062041 64
1793062046 64
```
</details>

---

