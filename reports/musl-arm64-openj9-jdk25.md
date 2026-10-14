---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-14 12:30:12 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 11 |
| CPU Cores (end) | 9 |
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
| Allocations | 60 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 168 |
| Sample Rate | 2.80/sec |
| Health Score | 175% |
| Threads | 14 |
| Allocations | 105 |

<details>
<summary>CPU Timeline (2 unique values: 9-11 cores)</summary>

```
1791995080 11
1791995085 11
1791995090 11
1791995095 11
1791995100 11
1791995105 11
1791995110 11
1791995115 11
1791995120 11
1791995125 11
1791995130 11
1791995135 11
1791995140 11
1791995145 11
1791995150 11
1791995155 11
1791995160 9
1791995165 9
1791995170 9
1791995175 9
```
</details>

---

