---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-09-29 11:52:34 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 40 |
| CPU Cores (end) | 52 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 104 |
| Sample Rate | 1.73/sec |
| Health Score | 108% |
| Threads | 13 |
| Allocations | 66 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 231 |
| Sample Rate | 3.85/sec |
| Health Score | 241% |
| Threads | 13 |
| Allocations | 116 |

<details>
<summary>CPU Timeline (2 unique values: 40-52 cores)</summary>

```
1790696822 40
1790696827 40
1790696832 40
1790696837 40
1790696842 40
1790696847 40
1790696852 40
1790696857 40
1790696862 40
1790696867 40
1790696872 40
1790696877 40
1790696882 40
1790696887 40
1790696892 40
1790696897 40
1790696902 52
1790696907 52
1790696912 52
1790696917 52
```
</details>

---

