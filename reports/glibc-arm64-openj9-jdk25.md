---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-19 01:06:10 EDT

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
| CPU Cores (start) | 14 |
| CPU Cores (end) | 16 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 354 |
| Sample Rate | 5.90/sec |
| Health Score | 369% |
| Threads | 8 |
| Allocations | 384 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 160 |
| Sample Rate | 2.67/sec |
| Health Score | 167% |
| Threads | 15 |
| Allocations | 134 |

<details>
<summary>CPU Timeline (3 unique values: 14-16 cores)</summary>

```
1792386080 14
1792386085 15
1792386090 15
1792386095 15
1792386100 15
1792386105 16
1792386110 16
1792386115 16
1792386120 16
1792386125 16
1792386130 16
1792386135 16
1792386140 16
1792386145 16
1792386150 16
1792386155 16
1792386160 16
1792386165 16
1792386170 16
1792386175 16
```
</details>

---

