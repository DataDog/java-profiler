---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-09 16:18:59 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 43 |
| CPU Cores (end) | 35 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 440 |
| Sample Rate | 7.33/sec |
| Health Score | 458% |
| Threads | 8 |
| Allocations | 351 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 67 |
| Sample Rate | 1.12/sec |
| Health Score | 70% |
| Threads | 10 |
| Allocations | 50 |

<details>
<summary>CPU Timeline (5 unique values: 35-45 cores)</summary>

```
1794258888 43
1794258893 43
1794258898 43
1794258903 43
1794258908 43
1794258913 43
1794258918 45
1794258923 45
1794258928 45
1794258933 45
1794258938 45
1794258943 45
1794258948 45
1794258953 45
1794258958 42
1794258963 42
1794258968 42
1794258973 42
1794258978 42
1794258983 37
```
</details>

---

