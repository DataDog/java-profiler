---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-05 05:59:39 EST

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
| CPU Cores (start) | 71 |
| CPU Cores (end) | 69 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 450 |
| Sample Rate | 7.50/sec |
| Health Score | 469% |
| Threads | 9 |
| Allocations | 391 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 599 |
| Sample Rate | 9.98/sec |
| Health Score | 624% |
| Threads | 11 |
| Allocations | 420 |

<details>
<summary>CPU Timeline (3 unique values: 69-90 cores)</summary>

```
1793876135 71
1793876140 71
1793876145 71
1793876150 71
1793876155 71
1793876160 71
1793876165 71
1793876170 71
1793876175 71
1793876180 71
1793876185 90
1793876190 90
1793876195 69
1793876200 69
1793876205 69
1793876210 69
1793876215 69
1793876220 69
1793876225 69
1793876230 69
```
</details>

---

