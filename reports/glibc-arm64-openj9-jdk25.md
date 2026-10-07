---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-07 10:29:42 EDT

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
| CPU Cores (start) | 43 |
| CPU Cores (end) | 39 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 81 |
| Sample Rate | 1.35/sec |
| Health Score | 84% |
| Threads | 10 |
| Allocations | 81 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 251 |
| Sample Rate | 4.18/sec |
| Health Score | 261% |
| Threads | 12 |
| Allocations | 130 |

<details>
<summary>CPU Timeline (3 unique values: 31-43 cores)</summary>

```
1791383073 43
1791383078 43
1791383083 31
1791383088 31
1791383093 31
1791383098 31
1791383103 31
1791383108 31
1791383113 31
1791383118 31
1791383123 31
1791383128 31
1791383133 31
1791383138 31
1791383143 31
1791383148 31
1791383153 39
1791383158 39
1791383163 39
1791383168 39
```
</details>

---

