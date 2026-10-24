---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-24 05:16:32 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 61 |
| CPU Cores (end) | 58 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 515 |
| Sample Rate | 8.58/sec |
| Health Score | 536% |
| Threads | 9 |
| Allocations | 360 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 676 |
| Sample Rate | 11.27/sec |
| Health Score | 704% |
| Threads | 10 |
| Allocations | 493 |

<details>
<summary>CPU Timeline (5 unique values: 57-63 cores)</summary>

```
1792833089 61
1792833094 61
1792833099 61
1792833104 61
1792833109 61
1792833114 61
1792833119 61
1792833124 61
1792833129 61
1792833134 61
1792833139 57
1792833144 57
1792833149 57
1792833154 57
1792833159 57
1792833164 59
1792833169 59
1792833174 61
1792833179 61
1792833184 63
```
</details>

---

