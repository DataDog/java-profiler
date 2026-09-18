---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-09-18 02:31:38 EDT

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 28 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 221 |
| Sample Rate | 3.68/sec |
| Health Score | 230% |
| Threads | 10 |
| Allocations | 162 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 72 |
| Sample Rate | 1.20/sec |
| Health Score | 75% |
| Threads | 9 |
| Allocations | 40 |

<details>
<summary>CPU Timeline (2 unique values: 28-48 cores)</summary>

```
1789712837 48
1789712842 48
1789712847 48
1789712852 48
1789712857 48
1789712862 48
1789712867 48
1789712873 48
1789712878 48
1789712883 48
1789712888 48
1789712893 48
1789712898 48
1789712903 48
1789712908 48
1789712913 48
1789712918 48
1789712923 48
1789712928 48
1789712933 48
```
</details>

---

