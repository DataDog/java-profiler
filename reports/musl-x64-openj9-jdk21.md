---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-28 12:04:40 EDT

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
| CPU Cores (start) | 85 |
| CPU Cores (end) | 91 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 494 |
| Sample Rate | 8.23/sec |
| Health Score | 514% |
| Threads | 9 |
| Allocations | 398 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 670 |
| Sample Rate | 11.17/sec |
| Health Score | 698% |
| Threads | 10 |
| Allocations | 492 |

<details>
<summary>CPU Timeline (2 unique values: 85-91 cores)</summary>

```
1793203126 85
1793203131 85
1793203136 85
1793203141 85
1793203146 85
1793203151 85
1793203156 85
1793203161 85
1793203166 85
1793203171 85
1793203176 85
1793203181 85
1793203186 85
1793203191 85
1793203196 91
1793203201 91
1793203206 91
1793203211 91
1793203216 91
1793203221 91
```
</details>

---

