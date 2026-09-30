---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-09-30 07:18:05 EDT

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
| CPU Cores (start) | 27 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 53 |
| Sample Rate | 0.88/sec |
| Health Score | 55% |
| Threads | 7 |
| Allocations | 63 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 53 |
| Sample Rate | 0.88/sec |
| Health Score | 55% |
| Threads | 10 |
| Allocations | 38 |

<details>
<summary>CPU Timeline (4 unique values: 27-43 cores)</summary>

```
1790766862 27
1790766867 27
1790766872 27
1790766877 27
1790766882 27
1790766887 27
1790766892 27
1790766897 27
1790766902 27
1790766908 27
1790766913 27
1790766918 27
1790766923 27
1790766928 27
1790766933 27
1790766938 27
1790766943 27
1790766948 39
1790766953 39
1790766958 34
```
</details>

---

