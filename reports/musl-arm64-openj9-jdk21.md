---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-09-22 07:06:12 EDT

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
| CPU Cores (start) | 24 |
| CPU Cores (end) | 29 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 77 |
| Sample Rate | 1.28/sec |
| Health Score | 80% |
| Threads | 10 |
| Allocations | 76 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 87 |
| Sample Rate | 1.45/sec |
| Health Score | 91% |
| Threads | 11 |
| Allocations | 53 |

<details>
<summary>CPU Timeline (2 unique values: 24-29 cores)</summary>

```
1790074837 24
1790074842 24
1790074847 24
1790074852 24
1790074857 24
1790074862 24
1790074867 24
1790074872 24
1790074877 29
1790074882 29
1790074887 29
1790074892 29
1790074897 29
1790074902 29
1790074907 29
1790074912 29
1790074917 29
1790074922 29
1790074927 29
1790074932 29
```
</details>

---

