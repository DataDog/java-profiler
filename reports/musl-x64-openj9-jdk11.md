---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-30 21:17:54 EDT

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
| CPU Cores (start) | 67 |
| CPU Cores (end) | 75 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 514 |
| Sample Rate | 8.57/sec |
| Health Score | 536% |
| Threads | 8 |
| Allocations | 418 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 725 |
| Sample Rate | 12.08/sec |
| Health Score | 755% |
| Threads | 10 |
| Allocations | 572 |

<details>
<summary>CPU Timeline (4 unique values: 67-75 cores)</summary>

```
1793409195 67
1793409200 67
1793409205 69
1793409210 69
1793409215 69
1793409220 69
1793409225 69
1793409230 67
1793409235 67
1793409240 67
1793409245 67
1793409250 67
1793409255 67
1793409260 67
1793409265 67
1793409270 70
1793409275 70
1793409280 70
1793409285 70
1793409290 70
```
</details>

---

