---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-10-14 12:30:09 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 46 |
| CPU Cores (end) | 43 |
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
| Allocations | 62 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 88 |
| Sample Rate | 1.47/sec |
| Health Score | 92% |
| Threads | 14 |
| Allocations | 45 |

<details>
<summary>CPU Timeline (3 unique values: 43-48 cores)</summary>

```
1791995086 46
1791995091 46
1791995096 46
1791995101 46
1791995106 46
1791995111 46
1791995116 46
1791995121 46
1791995126 46
1791995131 46
1791995136 48
1791995141 48
1791995146 48
1791995151 48
1791995156 48
1791995161 43
1791995166 43
1791995171 43
1791995176 43
1791995181 43
```
</details>

---

