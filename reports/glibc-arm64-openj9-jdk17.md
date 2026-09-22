---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-09-22 12:27:25 EDT

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
| CPU Cores (end) | 50 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 87 |
| Sample Rate | 1.45/sec |
| Health Score | 91% |
| Threads | 11 |
| Allocations | 71 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 108 |
| Sample Rate | 1.80/sec |
| Health Score | 112% |
| Threads | 14 |
| Allocations | 50 |

<details>
<summary>CPU Timeline (1 unique values: 50-50 cores)</summary>

```
1790093982 50
1790093987 50
1790093992 50
1790093997 50
1790094002 50
1790094007 50
1790094012 50
1790094017 50
1790094022 50
1790094027 50
1790094032 50
1790094037 50
1790094042 50
1790094047 50
1790094052 50
1790094057 50
1790094062 50
1790094067 50
1790094072 50
1790094077 50
```
</details>

---

