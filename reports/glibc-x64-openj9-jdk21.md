---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-10 14:54:02 EST

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
| CPU Cores (end) | 79 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 503 |
| Sample Rate | 8.38/sec |
| Health Score | 524% |
| Threads | 9 |
| Allocations | 357 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 719 |
| Sample Rate | 11.98/sec |
| Health Score | 749% |
| Threads | 11 |
| Allocations | 475 |

<details>
<summary>CPU Timeline (2 unique values: 79-81 cores)</summary>

```
1794340134 81
1794340139 81
1794340144 81
1794340149 81
1794340154 81
1794340159 81
1794340164 81
1794340169 81
1794340174 81
1794340179 81
1794340184 81
1794340189 81
1794340194 81
1794340199 81
1794340204 81
1794340209 81
1794340214 81
1794340219 81
1794340224 79
1794340229 79
```
</details>

---

