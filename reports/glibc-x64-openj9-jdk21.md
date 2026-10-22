---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-22 10:29:17 EDT

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
| CPU Cores (start) | 81 |
| CPU Cores (end) | 83 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 653 |
| Sample Rate | 10.88/sec |
| Health Score | 680% |
| Threads | 9 |
| Allocations | 356 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 747 |
| Sample Rate | 12.45/sec |
| Health Score | 778% |
| Threads | 10 |
| Allocations | 468 |

<details>
<summary>CPU Timeline (2 unique values: 81-83 cores)</summary>

```
1792679005 81
1792679010 81
1792679015 81
1792679020 83
1792679025 83
1792679030 83
1792679035 83
1792679040 83
1792679045 83
1792679050 83
1792679055 83
1792679060 83
1792679065 83
1792679070 83
1792679075 83
1792679080 83
1792679085 83
1792679090 83
1792679095 83
1792679100 83
```
</details>

---

