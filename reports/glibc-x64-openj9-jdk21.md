---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-10 11:01:16 EST

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
| CPU Cores (start) | 96 |
| CPU Cores (end) | 93 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 540 |
| Sample Rate | 9.00/sec |
| Health Score | 562% |
| Threads | 9 |
| Allocations | 373 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 649 |
| Sample Rate | 10.82/sec |
| Health Score | 676% |
| Threads | 11 |
| Allocations | 476 |

<details>
<summary>CPU Timeline (2 unique values: 93-96 cores)</summary>

```
1794326158 96
1794326163 96
1794326168 96
1794326173 96
1794326178 96
1794326183 96
1794326188 96
1794326193 96
1794326198 96
1794326203 96
1794326208 96
1794326213 96
1794326218 96
1794326223 96
1794326228 96
1794326233 96
1794326238 96
1794326243 96
1794326248 96
1794326253 93
```
</details>

---

