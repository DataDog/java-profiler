---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-27 19:06:19 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 31 |
| CPU Cores (end) | 31 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 89 |
| Sample Rate | 1.48/sec |
| Health Score | 92% |
| Threads | 9 |
| Allocations | 65 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1012 |
| Sample Rate | 16.87/sec |
| Health Score | 1054% |
| Threads | 9 |
| Allocations | 464 |

<details>
<summary>CPU Timeline (1 unique values: 31-31 cores)</summary>

```
1793142108 31
1793142113 31
1793142118 31
1793142123 31
1793142128 31
1793142133 31
1793142138 31
1793142143 31
1793142148 31
1793142153 31
1793142158 31
1793142163 31
1793142168 31
1793142173 31
1793142178 31
1793142183 31
1793142188 31
1793142193 31
1793142198 31
1793142203 31
```
</details>

---

