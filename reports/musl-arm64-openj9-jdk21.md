---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-09-21 04:44:08 EDT

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
| CPU Cores (start) | 38 |
| CPU Cores (end) | 41 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 49 |
| Sample Rate | 0.82/sec |
| Health Score | 51% |
| Threads | 8 |
| Allocations | 43 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 50 |
| Sample Rate | 0.83/sec |
| Health Score | 52% |
| Threads | 11 |
| Allocations | 41 |

<details>
<summary>CPU Timeline (3 unique values: 38-43 cores)</summary>

```
1789979848 38
1789979853 38
1789979858 38
1789979863 38
1789979868 38
1789979873 38
1789979878 38
1789979883 38
1789979888 38
1789979893 38
1789979898 38
1789979903 38
1789979908 38
1789979913 38
1789979918 38
1789979923 38
1789979928 38
1789979933 38
1789979938 38
1789979943 43
```
</details>

---

