---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-08-10 20:49:55 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 88 |
| CPU Cores (end) | 76 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 516 |
| Sample Rate | 8.60/sec |
| Health Score | 537% |
| Threads | 8 |
| Allocations | 372 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 841 |
| Sample Rate | 14.02/sec |
| Health Score | 876% |
| Threads | 11 |
| Allocations | 547 |

<details>
<summary>CPU Timeline (4 unique values: 76-90 cores)</summary>

```
1786409165 88
1786409170 88
1786409175 88
1786409180 88
1786409185 88
1786409190 90
1786409195 90
1786409200 90
1786409205 90
1786409210 90
1786409215 90
1786409220 84
1786409225 84
1786409230 76
1786409235 76
1786409240 76
1786409245 76
1786409250 76
1786409255 76
1786409260 76
```
</details>

---

