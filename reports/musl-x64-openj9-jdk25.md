---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-09-03 15:56:33 EDT

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
| CPU Cores (start) | 76 |
| CPU Cores (end) | 68 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 405 |
| Sample Rate | 6.75/sec |
| Health Score | 422% |
| Threads | 9 |
| Allocations | 412 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 586 |
| Sample Rate | 9.77/sec |
| Health Score | 611% |
| Threads | 10 |
| Allocations | 521 |

<details>
<summary>CPU Timeline (2 unique values: 68-76 cores)</summary>

```
1788465030 76
1788465035 76
1788465040 76
1788465045 76
1788465050 76
1788465055 76
1788465060 76
1788465065 76
1788465070 76
1788465075 76
1788465080 76
1788465085 76
1788465090 68
1788465095 68
1788465100 68
1788465105 68
1788465110 68
1788465115 68
1788465120 68
1788465125 68
```
</details>

---

