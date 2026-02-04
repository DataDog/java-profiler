---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-02-04 07:50:53 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 96 |
| CPU Cores (end) | 79 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 813 |
| Sample Rate | 13.55/sec |
| Health Score | 847% |
| Threads | 11 |
| Allocations | 403 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 775 |
| Sample Rate | 12.92/sec |
| Health Score | 807% |
| Threads | 12 |
| Allocations | 500 |

<details>
<summary>CPU Timeline (3 unique values: 79-96 cores)</summary>

```
1770209120 96
1770209125 96
1770209130 96
1770209135 96
1770209140 96
1770209145 96
1770209150 96
1770209155 96
1770209160 96
1770209165 96
1770209170 84
1770209175 84
1770209180 84
1770209185 84
1770209190 84
1770209195 84
1770209200 84
1770209205 84
1770209210 79
1770209215 79
```
</details>

---

