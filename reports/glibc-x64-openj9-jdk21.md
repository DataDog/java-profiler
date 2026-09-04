---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-09-04 05:50:50 EDT

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
| CPU Cores (start) | 76 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 667 |
| Sample Rate | 11.12/sec |
| Health Score | 695% |
| Threads | 10 |
| Allocations | 353 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 922 |
| Sample Rate | 15.37/sec |
| Health Score | 961% |
| Threads | 10 |
| Allocations | 476 |

<details>
<summary>CPU Timeline (2 unique values: 76-96 cores)</summary>

```
1788515235 76
1788515240 76
1788515245 76
1788515250 76
1788515255 76
1788515260 76
1788515265 76
1788515270 76
1788515275 76
1788515280 76
1788515285 76
1788515290 96
1788515295 96
1788515300 96
1788515305 96
1788515310 96
1788515315 96
1788515320 96
1788515325 96
1788515330 96
```
</details>

---

