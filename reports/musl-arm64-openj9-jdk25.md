---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-12 06:49:10 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 42 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 132 |
| Sample Rate | 2.20/sec |
| Health Score | 138% |
| Threads | 11 |
| Allocations | 75 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 86 |
| Sample Rate | 1.43/sec |
| Health Score | 89% |
| Threads | 14 |
| Allocations | 44 |

<details>
<summary>CPU Timeline (2 unique values: 42-48 cores)</summary>

```
1794483879 48
1794483884 48
1794483889 48
1794483894 48
1794483899 48
1794483904 48
1794483909 48
1794483914 48
1794483919 48
1794483924 48
1794483929 48
1794483934 48
1794483939 48
1794483944 48
1794483949 48
1794483954 48
1794483959 48
1794483964 48
1794483969 48
1794483974 48
```
</details>

---

