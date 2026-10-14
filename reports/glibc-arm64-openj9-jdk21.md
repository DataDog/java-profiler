---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-14 12:30:10 EDT

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
| CPU Cores (start) | 45 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 52 |
| Sample Rate | 0.87/sec |
| Health Score | 54% |
| Threads | 8 |
| Allocations | 65 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 171 |
| Sample Rate | 2.85/sec |
| Health Score | 178% |
| Threads | 12 |
| Allocations | 120 |

<details>
<summary>CPU Timeline (3 unique values: 45-48 cores)</summary>

```
1791995090 45
1791995095 45
1791995100 45
1791995105 45
1791995110 45
1791995115 45
1791995120 45
1791995125 45
1791995130 45
1791995135 46
1791995140 46
1791995145 48
1791995150 48
1791995155 48
1791995160 48
1791995165 48
1791995170 48
1791995175 48
1791995180 48
1791995185 48
```
</details>

---

