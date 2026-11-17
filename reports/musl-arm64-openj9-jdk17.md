---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-17 16:21:38 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 38 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 335 |
| Sample Rate | 5.58/sec |
| Health Score | 349% |
| Threads | 10 |
| Allocations | 143 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 316 |
| Sample Rate | 5.27/sec |
| Health Score | 329% |
| Threads | 12 |
| Allocations | 140 |

<details>
<summary>CPU Timeline (3 unique values: 38-51 cores)</summary>

```
1794950096 38
1794950101 38
1794950106 38
1794950111 38
1794950116 51
1794950121 51
1794950126 51
1794950131 51
1794950136 51
1794950141 51
1794950146 51
1794950151 46
1794950156 46
1794950161 46
1794950166 46
1794950171 46
1794950176 46
1794950181 46
1794950186 46
1794950191 46
```
</details>

---

