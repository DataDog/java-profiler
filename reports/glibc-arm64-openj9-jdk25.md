---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-26 12:32:04 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 31 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 537 |
| Sample Rate | 8.95/sec |
| Health Score | 559% |
| Threads | 8 |
| Allocations | 405 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 84 |
| Sample Rate | 1.40/sec |
| Health Score | 87% |
| Threads | 13 |
| Allocations | 45 |

<details>
<summary>CPU Timeline (3 unique values: 31-43 cores)</summary>

```
1793032020 31
1793032025 31
1793032030 31
1793032035 31
1793032040 31
1793032045 36
1793032050 36
1793032055 36
1793032060 36
1793032065 36
1793032070 36
1793032075 36
1793032080 36
1793032085 36
1793032090 36
1793032095 36
1793032100 36
1793032105 31
1793032110 31
1793032115 31
```
</details>

---

