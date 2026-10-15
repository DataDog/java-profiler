---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-15 07:15:50 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 23 |
| CPU Cores (end) | 23 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 190 |
| Sample Rate | 3.17/sec |
| Health Score | 198% |
| Threads | 11 |
| Allocations | 137 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 196 |
| Sample Rate | 3.27/sec |
| Health Score | 204% |
| Threads | 12 |
| Allocations | 111 |

<details>
<summary>CPU Timeline (2 unique values: 22-23 cores)</summary>

```
1792062650 23
1792062655 23
1792062660 23
1792062665 23
1792062670 23
1792062675 23
1792062680 23
1792062685 23
1792062690 22
1792062695 22
1792062700 22
1792062705 22
1792062710 23
1792062715 23
1792062720 23
1792062725 23
1792062730 23
1792062735 23
1792062740 23
1792062745 23
```
</details>

---

