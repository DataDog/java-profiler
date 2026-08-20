---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-08-20 06:18:39 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 45 |
| CPU Cores (end) | 40 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 194 |
| Sample Rate | 3.23/sec |
| Health Score | 202% |
| Threads | 9 |
| Allocations | 149 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 52 |
| Sample Rate | 0.87/sec |
| Health Score | 54% |
| Threads | 11 |
| Allocations | 63 |

<details>
<summary>CPU Timeline (2 unique values: 40-45 cores)</summary>

```
1787220868 45
1787220873 45
1787220878 45
1787220883 45
1787220888 45
1787220893 45
1787220898 45
1787220903 45
1787220908 45
1787220913 45
1787220918 45
1787220923 40
1787220928 40
1787220933 40
1787220938 40
1787220943 40
1787220948 40
1787220953 40
1787220958 40
1787220963 40
```
</details>

---

