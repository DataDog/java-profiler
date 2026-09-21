---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-09-21 04:44:08 EDT

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
| CPU Cores (start) | 41 |
| CPU Cores (end) | 41 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 47 |
| Sample Rate | 0.78/sec |
| Health Score | 49% |
| Threads | 7 |
| Allocations | 69 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 8 |
| Sample Rate | 0.13/sec |
| Health Score | 8% |
| Threads | 7 |
| Allocations | 5 |

<details>
<summary>CPU Timeline (2 unique values: 41-43 cores)</summary>

```
1789979838 41
1789979843 41
1789979848 41
1789979853 41
1789979858 43
1789979863 43
1789979868 43
1789979873 43
1789979878 43
1789979883 43
1789979888 43
1789979893 43
1789979898 43
1789979903 43
1789979908 43
1789979913 41
1789979918 41
1789979923 41
1789979928 41
1789979933 41
```
</details>

---

