---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-17 16:21:36 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 43 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 83 |
| Sample Rate | 1.38/sec |
| Health Score | 86% |
| Threads | 11 |
| Allocations | 73 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 269 |
| Sample Rate | 4.48/sec |
| Health Score | 280% |
| Threads | 14 |
| Allocations | 132 |

<details>
<summary>CPU Timeline (2 unique values: 30-43 cores)</summary>

```
1794950121 43
1794950126 43
1794950131 43
1794950136 43
1794950141 43
1794950146 43
1794950151 43
1794950156 43
1794950161 43
1794950166 43
1794950171 43
1794950176 43
1794950181 43
1794950186 43
1794950191 43
1794950196 43
1794950201 43
1794950206 43
1794950211 43
1794950216 43
```
</details>

---

