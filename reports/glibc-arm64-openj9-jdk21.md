---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-29 06:55:47 EDT

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
| CPU Cores (start) | 39 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 79 |
| Sample Rate | 1.32/sec |
| Health Score | 82% |
| Threads | 12 |
| Allocations | 67 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 82 |
| Sample Rate | 1.37/sec |
| Health Score | 86% |
| Threads | 13 |
| Allocations | 49 |

<details>
<summary>CPU Timeline (2 unique values: 39-51 cores)</summary>

```
1793271079 39
1793271084 39
1793271089 39
1793271094 39
1793271099 39
1793271104 39
1793271109 39
1793271114 39
1793271119 39
1793271124 39
1793271129 39
1793271134 39
1793271139 39
1793271144 39
1793271149 39
1793271154 39
1793271159 39
1793271164 51
1793271169 51
1793271174 51
```
</details>

---

