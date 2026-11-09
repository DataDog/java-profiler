---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-09 09:27:57 EST

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
| CPU Cores (start) | 41 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 509 |
| Sample Rate | 8.48/sec |
| Health Score | 530% |
| Threads | 9 |
| Allocations | 380 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 645 |
| Sample Rate | 10.75/sec |
| Health Score | 672% |
| Threads | 10 |
| Allocations | 507 |

<details>
<summary>CPU Timeline (2 unique values: 41-46 cores)</summary>

```
1794234136 41
1794234141 41
1794234146 41
1794234151 41
1794234156 41
1794234161 46
1794234166 46
1794234171 46
1794234176 46
1794234181 46
1794234186 46
1794234191 46
1794234196 46
1794234201 46
1794234206 46
1794234211 46
1794234216 46
1794234221 46
1794234226 46
1794234231 46
```
</details>

---

