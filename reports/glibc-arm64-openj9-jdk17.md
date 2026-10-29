---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-10-29 11:55:54 EDT

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
| CPU Cores (start) | 50 |
| CPU Cores (end) | 49 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 198 |
| Sample Rate | 3.30/sec |
| Health Score | 206% |
| Threads | 9 |
| Allocations | 176 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 53 |
| Sample Rate | 0.88/sec |
| Health Score | 55% |
| Threads | 12 |
| Allocations | 37 |

<details>
<summary>CPU Timeline (3 unique values: 48-50 cores)</summary>

```
1793289008 50
1793289013 50
1793289018 50
1793289023 50
1793289028 50
1793289033 48
1793289038 48
1793289043 48
1793289048 48
1793289053 48
1793289058 49
1793289063 49
1793289068 49
1793289073 49
1793289078 49
1793289083 49
1793289088 49
1793289093 49
1793289098 49
1793289103 49
```
</details>

---

