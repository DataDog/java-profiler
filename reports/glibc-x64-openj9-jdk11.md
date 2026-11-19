---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-19 06:06:30 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 67 |
| CPU Cores (end) | 72 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 570 |
| Sample Rate | 9.50/sec |
| Health Score | 594% |
| Threads | 8 |
| Allocations | 363 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 706 |
| Sample Rate | 11.77/sec |
| Health Score | 736% |
| Threads | 9 |
| Allocations | 499 |

<details>
<summary>CPU Timeline (4 unique values: 65-72 cores)</summary>

```
1795085943 67
1795085948 67
1795085953 67
1795085958 65
1795085963 65
1795085968 65
1795085973 65
1795085978 65
1795085983 65
1795085988 65
1795085993 65
1795085998 65
1795086003 65
1795086008 65
1795086013 65
1795086018 65
1795086023 70
1795086028 70
1795086033 70
1795086038 70
```
</details>

---

