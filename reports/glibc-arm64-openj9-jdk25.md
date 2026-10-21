---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-21 10:48:09 EDT

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 40 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 76 |
| Sample Rate | 1.27/sec |
| Health Score | 79% |
| Threads | 11 |
| Allocations | 57 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 110 |
| Sample Rate | 1.83/sec |
| Health Score | 114% |
| Threads | 11 |
| Allocations | 62 |

<details>
<summary>CPU Timeline (2 unique values: 40-48 cores)</summary>

```
1792593841 48
1792593846 48
1792593851 48
1792593856 48
1792593861 48
1792593866 48
1792593871 48
1792593876 48
1792593881 48
1792593886 48
1792593892 48
1792593897 48
1792593902 48
1792593907 48
1792593912 40
1792593917 40
1792593922 40
1792593927 40
1792593932 40
1792593937 40
```
</details>

---

