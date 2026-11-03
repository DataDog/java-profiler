---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-03 16:51:01 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 90 |
| CPU Cores (end) | 94 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 505 |
| Sample Rate | 8.42/sec |
| Health Score | 526% |
| Threads | 9 |
| Allocations | 345 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 621 |
| Sample Rate | 10.35/sec |
| Health Score | 647% |
| Threads | 11 |
| Allocations | 492 |

<details>
<summary>CPU Timeline (3 unique values: 90-94 cores)</summary>

```
1793742194 90
1793742200 90
1793742205 90
1793742210 90
1793742215 90
1793742220 90
1793742225 90
1793742230 90
1793742235 90
1793742240 92
1793742245 92
1793742250 92
1793742255 92
1793742260 92
1793742265 92
1793742270 92
1793742275 92
1793742280 92
1793742285 92
1793742290 92
```
</details>

---

