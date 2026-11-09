---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-09 16:19:01 EST

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
| CPU Cores (start) | 39 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 107 |
| Sample Rate | 1.78/sec |
| Health Score | 111% |
| Threads | 10 |
| Allocations | 61 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 724 |
| Sample Rate | 12.07/sec |
| Health Score | 754% |
| Threads | 11 |
| Allocations | 542 |

<details>
<summary>CPU Timeline (3 unique values: 39-48 cores)</summary>

```
1794258883 39
1794258888 39
1794258893 39
1794258898 39
1794258903 44
1794258908 44
1794258913 44
1794258918 44
1794258923 44
1794258928 44
1794258933 44
1794258938 44
1794258943 44
1794258948 44
1794258953 44
1794258958 44
1794258963 48
1794258968 48
1794258973 48
1794258978 48
```
</details>

---

