---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-17 16:21:36 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 15 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 99 |
| Sample Rate | 1.65/sec |
| Health Score | 103% |
| Threads | 8 |
| Allocations | 75 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 726 |
| Sample Rate | 12.10/sec |
| Health Score | 756% |
| Threads | 10 |
| Allocations | 431 |

<details>
<summary>CPU Timeline (2 unique values: 15-51 cores)</summary>

```
1794950126 15
1794950131 15
1794950136 15
1794950141 15
1794950146 15
1794950151 15
1794950156 15
1794950161 15
1794950166 15
1794950171 15
1794950176 15
1794950181 15
1794950186 15
1794950191 15
1794950196 15
1794950201 15
1794950206 15
1794950211 15
1794950216 15
1794950221 15
```
</details>

---

