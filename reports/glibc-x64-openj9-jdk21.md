---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-11 06:07:52 EST

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
| CPU Cores (start) | 63 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 497 |
| Sample Rate | 8.28/sec |
| Health Score | 517% |
| Threads | 9 |
| Allocations | 366 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 659 |
| Sample Rate | 10.98/sec |
| Health Score | 686% |
| Threads | 9 |
| Allocations | 462 |

<details>
<summary>CPU Timeline (2 unique values: 30-63 cores)</summary>

```
1794395011 63
1794395016 30
1794395021 30
1794395026 30
1794395031 30
1794395036 30
1794395041 30
1794395046 30
1794395051 30
1794395056 30
1794395061 30
1794395066 30
1794395071 30
1794395076 30
1794395081 30
1794395086 30
1794395091 30
1794395096 30
1794395101 30
1794395106 30
```
</details>

---

