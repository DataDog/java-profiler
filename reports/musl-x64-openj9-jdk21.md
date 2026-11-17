---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-17 16:21:39 EST

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
| CPU Cores (start) | 60 |
| CPU Cores (end) | 52 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 556 |
| Sample Rate | 9.27/sec |
| Health Score | 579% |
| Threads | 9 |
| Allocations | 398 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 712 |
| Sample Rate | 11.87/sec |
| Health Score | 742% |
| Threads | 11 |
| Allocations | 512 |

<details>
<summary>CPU Timeline (5 unique values: 52-75 cores)</summary>

```
1794950071 60
1794950076 60
1794950081 60
1794950086 62
1794950091 62
1794950096 62
1794950101 62
1794950106 52
1794950111 52
1794950116 52
1794950121 52
1794950126 52
1794950131 52
1794950136 52
1794950141 52
1794950146 52
1794950151 52
1794950156 52
1794950161 52
1794950166 52
```
</details>

---

