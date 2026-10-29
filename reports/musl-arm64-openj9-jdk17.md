---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-10-29 06:55:49 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 13 |
| CPU Cores (end) | 18 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 77 |
| Sample Rate | 1.28/sec |
| Health Score | 80% |
| Threads | 9 |
| Allocations | 68 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 81 |
| Sample Rate | 1.35/sec |
| Health Score | 84% |
| Threads | 13 |
| Allocations | 42 |

<details>
<summary>CPU Timeline (2 unique values: 13-18 cores)</summary>

```
1793271024 13
1793271029 13
1793271034 13
1793271039 13
1793271044 13
1793271049 18
1793271054 18
1793271059 18
1793271064 18
1793271069 18
1793271074 18
1793271079 18
1793271084 18
1793271089 18
1793271094 18
1793271099 18
1793271104 18
1793271109 18
1793271114 18
1793271119 18
```
</details>

---

